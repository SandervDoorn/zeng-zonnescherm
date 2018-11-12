/*
 * protocolhandeler.c
 *
 * Created: 02/11/2018 11:22:35
 *  Author: Sander
 * 
 * Serial communication handler
 * 
 */ 


#include "serial.h"
#include "protocolhandeler.h"

/*Setters*/
void set_shutter_mode(uint8_t shutter_mode)
{
	eeprom_update_byte((uint8_t*)shutter_mode_adr, shutter_mode);
}

void set_shutter_state(uint8_t shutter_state)
{
	eeprom_update_byte((uint8_t*)shutter_state_adr, shutter_state);
}

void set_ths_temp(int16_t ths_temp)
{
	eeprom_update_byte((int16_t*)ths_temp_adr, ths_temp);
}

void set_ths_light(uint8_t ths_light)
{
	eeprom_update_byte((uint8_t*)ths_light_adr, ths_light);
}

void set_ths_dist(uint8_t ths_dist)
{
	eeprom_update_byte((uint8_t*)ths_dist_adr, ths_dist);
}

set_arduino_name(char* str)
{
	uint8_t i = 0;
	while(strlen(str)>i)
	{
		eeprom_update_byte((char*)name_start_adr+i, str[i]);
		i++;
	}
	eeprom_update_byte((char*)name_start_adr+i, '\0');
}

/*Getters*/
uint8_t get_shutter_mode()
{
	return eeprom_read_byte((uint8_t*)shutter_mode_adr);
}

uint8_t get_shutter_state()
{
	return eeprom_read_byte((uint8_t*)shutter_state_adr);
}

int16_t get_ths_temp()
{
	return eeprom_read_byte((uint16_t*)ths_temp_adr);
}

uint8_t get_ths_light()
{
	return eeprom_read_byte((uint8_t*)ths_light_adr);
}

uint8_t get_ths_dist()
{
	return eeprom_read_byte((uint8_t*)ths_dist_adr);
}

char* get_arduino_name()
{
	uint8_t i = 0;
	uint8_t str[20];
	do
	{
		str[i] = eeprom_read_byte((char*)name_start_adr+i);
		i++;
	}while(str[i-1] != '\0');
	return str;
}

int open_screen()
{
	if (get_shutter_state() != OPEN)
	{
		set_shutter_state(1);
		return 1;
	}
	return 0;
}

int close_screen()
{
	if (get_shutter_state() != CLOSED)
	{
		set_shutter_state(0);
		return 1;
	}
	return 0;
}

//Source: https://stackoverflow.com/questions/14422775/how-to-check-a-given-string-contains-only-number-or-not-in-c
int numbers_only(const char *s)
{
	while (*s) {
		if (isdigit(*s++) == 0) return 0;
	}

	return 1;
}

void read_command()
{
	char commando[30];
	char arg[20];
	char inputbuffer[30];
	char response[100];

	//Reading command
	read_ser(inputbuffer, sizeof(inputbuffer));
	
	if (inputbuffer[0] == '\0')
	{
		return;
	}
	
	int i = 0;
	while (inputbuffer[i] != ' ' && inputbuffer[i] != '\0')
	{
		commando[i] = inputbuffer[i];
		i++;
	}
	commando[i] = '\0';

	i++; //Spatie skippen
	int j = 0;

	while (inputbuffer[i] != ' ' && inputbuffer[i] != '\0')
	{
		arg[j] = inputbuffer[i];
		i++;
		j++;
	}

	arg[j] = '\0';

	//Handshake to verify we are indeed Groot
	if (strcmp(commando, "WHO_ARE_YOU") == 0)
	{
		write_ser("I AM GROOT");
	}

	//Provide controller with all default settings
	if (strcmp(commando, "GET_SETTINGS")==0)
	{
		sprintf(response, "%s %i %i %i %i", get_arduino_name(), get_shutter_mode(), get_shutter_state(), get_ths_temp(), get_ths_dist());
		write_ser(response);
	}

	//If tree to handle all GETTERS
	if (strcmp(commando, "get_adruino_name") == 0)
	{
		if (get_arduino_name() !=NULL)
		{
			sprintf(response, "OK %s", get_arduino_name());
			write_ser(response);
		}
		else
		{
			write_ser("ERROR 601: Name is not set");
		}
	}

	if (strcmp(commando, "GET_STATE") == 0)
	{
		if (get_shutter_state() == OPEN || get_shutter_state == CLOSED)
		{
			sprintf(response, "OK %i", get_shutter_state());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 601: Unrecognized screenstate %i", get_shutter_state());
			write_ser(response);
		}
	}

	if (strcmp(commando, "GET_MODE") == 0)
	{
		if (get_shutter_mode()==MANUAL || get_shutter_mode() == AUTO)
		{
			sprintf(response, "OK %i", get_shutter_mode());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 601: Unrecognized mode %i", get_shutter_mode());
			write_ser(response);
		}
	}

	if (strcmp(commando, "GET_THS_TEMP") == 0)
	{
		if (get_ths_temp()!=NULL)
		{
			sprintf(response, "OK %i", get_ths_temp());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 442: Could not read value");
			write_ser(response);
		}
	}

	if (strcmp(commando, "GET_THS_DIST") == 0)
	{
		if (get_ths_dist()!=NULL)
		{
			sprintf(response, "OK %i", get_ths_dist());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 444: Could not read value");
			write_ser(response);
		}
	}

	if (strcmp(commando, "GET_SENSOR_TEMP") == 0)
	{
		if (read_sensor_temp()!=NULL && read_sensor_temp() <= 50)
		{
			sprintf(response, "OK %i", read_sensor_temp());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 442: Unrealistic value %i. Sensor might be defect", read_sensor_temp());
			write_ser(response);
		}
	}

	if (strcmp(commando, "GET_SENSOR_LIGHT") == 0)
	{
		if (read_sensor_light()!=NULL && read_sensor_light() <= 255)
		{
			sprintf(response, "OK %i", read_sensor_light());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 443: Unrealistic value %i. Sensor might be defect", read_sensor_light());
			write_ser(response);
		}
	}

	//If tree to handle all SETTERS
	if (strcmp(commando, "SET_NAME") == 0)
	{
		if (strlen(arg) > 0 && strlen(arg) <= 20)
		{
			set_arduino_name(arg);
			sprintf(response, "OK %s", get_arduino_name());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 605: Value %s not within limit 0-20", arg);
			write_ser(response);
		}
	}

	if (strcmp(commando, "SET_THS_TEMP") == 0)
	{
		if(numbers_only(arg)==1 && atoi(arg) <= 50)
		{
			uint8_t val = atoi(arg);
			set_ths_temp(val);
			sprintf(response, "OK %i", get_ths_temp());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 106: Invalid value %s", arg);
			write_ser(response);
		}
	}

	if (strcmp(commando, "SET_THS_DIST") == 0)
	{
		if(numbers_only(arg)==1 && atoi(arg) >= 3 && atoi(arg) <= 30)
		{
			uint8_t val = atoi(arg);
			set_ths_dist(val);
			sprintf(response, "OK %i", get_ths_dist());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 107: Invalid value %s", arg);
			write_ser(response);
		}
	}

	if (strcmp(commando, "SET_STATE") == 0)
	{
		if (strcmp(arg, "OPEN") == 0)
		{
			if (get_shutter_state()!=OPEN && open_screen() == 1)
			{
				sprintf(response, "OK OPENING");
				write_ser(response);
			}
			else if (open_screen() == 0)
			{
				sprintf(response, "ERROR 105: Could not open screen");
				write_ser(response);
			}
		}

		if (strcmp(arg, "CLOSED") == 0)
		{
			if (get_shutter_state()!=CLOSED && close_screen() == 1)
			{
				sprintf(response, "OK CLOSING");
				write_ser(response);
			}
			else if (close_screen() == 0)
			{
				sprintf(response, "ERROR 105: Could not close screen");
				write_ser(response);
			}
		}
	}

	if (strcmp(commando, "SET_MODE") == 0)
	{
		if (strcmp(arg, "MANUAL") == 0)
		{
			if (get_shutter_mode()!=MANUAL)
			{
				set_shutter_mode(MANUAL);
				sprintf(response, "OK MODE MANUAL");
				write_ser(response);
			}
			else
			{
				sprintf(response, "ERROR 441: Could not set modus %s", arg);
				write_ser(response);
			}
		}

		if (strcmp(arg, "AUTO") == 0)
		{
			if (get_shutter_mode()!=AUTO)
			{
				set_shutter_mode(AUTO);
				sprintf(response, "OK MODE AUTO");
				write_ser(response);
			}
			else
			{
				sprintf(response, "ERROR 441: Could not set modus %s", arg);
				write_ser(response);
			}
		}
		inputbuffer[0] = '\0';
	}
}
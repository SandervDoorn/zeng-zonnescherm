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
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <avr/io.h>

#define MANUAL 0
#define AUTO 1

#define CLOSED 0
#define OPEN 1

//Temp placeholder functions
char name[20] = "Sander";
uint8_t ths_temp = 20;
uint8_t ths_dist = 20;
uint8_t state = CLOSED;
uint8_t mode = MANUAL;

char* get_name()
{
	return name;
}

void set_name(char* val)
{
	int i = 0;
	while (val[i] != '\0')
	{
		name[i] = val[i];
		i++;
	}
	name[i] = '\0';
}

uint8_t get_screen_state()
{
	return state;
}

void set_state(val)
{
	state = val;
}

int get_screen_mode()
{
	return mode;
}

void set_mode(val)
{
	mode = val;
}

uint8_t get_ths_temp()
{
	return ths_temp;
}

void set_ths_temp(uint8_t val)
{
	ths_temp = val;
}

uint8_t get_ths_dist()
{
	return ths_dist;
}

void set_ths_dist(uint8_t val)
{
	ths_dist = val;
}

uint8_t get_sens_temp()
{
	return 50;
}

char* get_sens_light()
{
	return "007";
}

int open_screen()
{
	if (state != OPEN)
	{
		set_state(1);
		return 1;
	}
	return 0;
}

int close_screen()
{
	if (state != CLOSED)
	{
		set_state(0);
		return 1;
	}
	return 0;
}

//End of placeholders

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
		sprintf(response, "%s %i %i %i %i", get_name(), get_screen_mode(), get_screen_state(), get_ths_temp(), get_ths_dist());
		write_ser(response);
	}

	//If tree to handle all GETTERS
	if (strcmp(commando, "GET_NAME") == 0)
	{
		if (name!=NULL)
		{
			sprintf(response, "OK %s", get_name());
			write_ser(response);
		}
		else
		{
			write_ser("ERROR 601: Name is not set");
		}
	}

	if (strcmp(commando, "GET_STATE") == 0)
	{
		if (state == OPEN || state == CLOSED)
		{
			sprintf(response, "OK %i", get_screen_state());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 601: Unrecognized screenstate %i", get_screen_state());
			write_ser(response);
		}
	}

	if (strcmp(commando, "GET_MODE") == 0)
	{
		if (get_screen_mode()==MANUAL || get_screen_state() == AUTO)
		{
			sprintf(response, "OK %i", get_screen_mode());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 601: Unrecognized mode %i", get_screen_mode());
			write_ser(response);
		}
	}

	if (strcmp(commando, "GET_THS_TEMP") == 0)
	{
		if (ths_temp!=NULL)
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
		if (ths_dist!=NULL)
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
		if (get_sens_temp()!=NULL && get_sens_temp() <= 50)
		{
			sprintf(response, "OK %i", get_sens_temp());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 442: Unrealistic value %i. Sensor might be defect", get_sens_temp());
			write_ser(response);
		}
	}

	if (strcmp(commando, "GET_SENSOR_LIGHT") == 0)
	{
		if (get_sens_light()!=NULL && get_sens_light() <= 255)
		{
			sprintf(response, "OK %i", get_sens_light());
			write_ser(response);
		}
		else
		{
			sprintf(response, "ERROR 443: Unrealistic value %i. Sensor might be defect", get_sens_light());
			write_ser(response);
		}
	}

	//If tree to handle all SETTERS
	if (strcmp(commando, "SET_NAME") == 0)
	{
		if (strlen(arg) > 0 && strlen(arg) <= 20)
		{
			set_name(arg);
			sprintf(response, "OK %s", get_name());
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
			if (state!=OPEN && open_screen() == 1)
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
			if (state!=CLOSED && close_screen() == 1)
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
			if (mode!=MANUAL)
			{
				set_mode(MANUAL);
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
			if (mode!=AUTO)
			{
				set_mode(AUTO);
				sprintf(response, "OK MODE AUTO");
				write_ser(response);
			}
			else
			{
				sprintf(response, "ERROR 441: Could not set modus %s", arg);
				write_ser(response);
			}
		}
	}
}

int main(void)
{
	init_serial();
	while(1)
	{
		read_command();
	}	
}
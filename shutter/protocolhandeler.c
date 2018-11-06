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
#include <string.h>
#include <avr/io.h>

//Temp placeholder functions
volatile char name[20] = "Sander";
volatile char ths_temp[3] = "20";
volatile char ths_dist[3] = "30";
volatile char screen_state[7] = "CLOSED";

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

char* get_screen_state()
{
	return screen_state;
}

char* get_screen_mode()
{
	return "MANUAL";
}

char* get_thold_temp()
{
	return ths_temp;
}

void set_thold_temp(char* val)
{
	int i = 0;
	while (val[i] != '\0')
	{
		ths_temp[i] = val[i];
		i++;
	}
	ths_temp[i];
}

char* get_thold_dist()
{
	return "030";
}

char* get_sens_temp()
{
	return "018";
}

char* get_sens_light()
{
	return "007";
}

void read_command()
{
	
	char response[30];
	char inputbuffer[50];
	char commando[30];
	char arg[20];

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
	if (strcmp(commando, "WHO_ARE_YOU")==0)
	{
		write_ser("I AM GROOT");
	}
	
	//If tree to handle all GETTERS
	if (strcmp(commando, "GET_NAME") == 0)
	{
		write_ser(get_name());
	}
	
	if (strcmp(commando, "GET_STATE_SCREEN") == 0)
	{
		write_ser(get_screen_state());
	}
	
	if (strcmp(commando, "GET_MODE") == 0)
	{
		write_ser(get_screen_mode());
	}
	
	if (strcmp(commando, "GET_THOLD_TEMP") == 0)
	{
		write_ser(get_thold_temp());
	}
	
	if (strcmp(commando, "GET_THOLD_DIST") == 0)
	{
		write_ser(get_thold_dist());
	}
	
	if (strcmp(commando, "GET_SENSOR_TEMP") == 0)
	{
		write_ser(get_sens_temp());
	}
	
	if (strcmp(commando, "GET_SENSOR_LIGHT") == 0)
	{
		write_ser(get_sens_light());
	}
	
	//If tree to handle all SETTERS
	if (strcmp(commando, "SET_NAME") == 0)
	{	
		set_name(arg);
		write_ser(name);
	}
	
	if (strcmp(commando, "SET_THOLD_TEMP") == 0)
	{
		set_thold_temp(arg);
		write_ser(ths_temp);
	}
	
	if (strcmp(commando, "SET_THOLD_DIST") == 0)
	{
		//set_thold_dist(arg);
		write_ser(ths_dist);
	}
	
	if (strcmp(commando, "SET_SCREEN") == 0)
	{
		if (strcmp(arg, "OPEN") == 0)
		{
			//open_screen();
			//write_ser(screen_state);
			write_ser("OPEN");
		}
		if (strcmp(arg, "CLOSED") == 0)
		{
			//close_screen();
			//write_ser(screen_state);
			write_ser("CLOSED");
		}
	}
	
	if (strcmp(commando, "SET_MODE") == 0)
	{
		if (strcmp(arg, "AUTO") == 0)
		{
			//set_mode("AUTO");
			write_ser("MODE AUTO");
		}
		if (strcmp(arg, "MANUAL") == 0)
		{
			//set_mode("MANUAL")
			write_ser("MODE MANUAL");
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
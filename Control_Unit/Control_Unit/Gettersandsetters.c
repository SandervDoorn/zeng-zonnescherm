#include <avr/eeprom.h>
#include <avr/io.h>
#include <stdint.h>
#include "GettersAndSetters.h"

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
	
	printf("Set_name = %s \n", str);
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
	printf("Get_name = %s \n", str);
	return str;
}
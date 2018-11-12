/*
 * protocolhandeler.h
 *
 * Created: 6-11-2018 12:10:35
 *  Author: Sander-Laptop
 */ 

#ifndef PROTOCOLHANDELER_H_
#define PROTOCOLHANDELER_H_

#include <avr/eeprom.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <avr/io.h>

/*
ths = threshold
adr = adress
*/
#define shutter_mode_adr 0
#define shutter_state_adr 1
#define ths_temp_adr 2
#define ths_light_adr 3
#define ths_dist_adr 4
#define name_start_adr 5

#define MANUAL 0
#define AUTO 1

#define CLOSED 0
#define OPEN 1

void set_shutter_mode(uint8_t shutter_mode);
void set_shutter_state(uint8_t shutter_state);
void set_ths_temp(int16_t ths_temp);
void set_ths_light(uint8_t ths_light);
void set_ths_dist(uint8_t ths_dist);
void set_arduino_name(char *str);

uint8_t get_shutter_mode();
uint8_t get_shutter_state();
int16_t get_ths_temp();
uint8_t get_ths_light();
uint8_t get_ths_dist();
char* get_arduino_name();

int open_screen();
int close_screen();

void read_command();


#endif /* PROTOCOLHANDELER_H_ */
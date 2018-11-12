#define F_CPU 16E6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


/*
PORTB0 The red LED
PORTB1 The yellow LED
PORTB2 The green LED
*/

void init_shutter();
uint8_t moving();
void auto_regulator();
void manual_regulator();
void init_leds();
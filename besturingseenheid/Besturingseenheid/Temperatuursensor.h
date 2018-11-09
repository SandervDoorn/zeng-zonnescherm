#define F_CPU 16E6
#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#define UBBRVAL 103

void ser_stdio_putchar(char c, FILE *stream);
void ser_init();
void ser_transmit(uint8_t data);
uint8_t ser_receive();
void ser_readln(char* buf, int maxlength, uint8_t echo); 

void init_adc_temp();
uint8_t get_adc_value_temp();
int8_t read_sensor_temp();

#define F_CPU 16E6
#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#define UBBRVAL 103

/* 
init_adc_temp sets the port to receive analog signals on Pin A0.
Then it enables the ADC.
*/
void init_adc_temp();

/*
get_adc_value_temp starts the conversion and returns ADCH.
ADCH contains the most significant 8 bits from the ADC value.
*/
uint8_t get_adc_value_temp();

/*
read_sensor_temp initiates the init_adc_temp.
Then it stores, in the variable sensor_temp the value from the ADCH.
The sensor_temp is then used to calculate the voltage.
Based on the voltage the degrees Celsius is calculated.
Lastly, return the Celsius.
*/
int8_t read_sensor_temp();

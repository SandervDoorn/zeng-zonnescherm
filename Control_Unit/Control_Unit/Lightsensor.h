#define F_CPU 16E6
#include <avr/io.h>

/*
init_adc_light sets the port to receive analog signals on Pin A1.
Then it enables the ADC.
*/
void init_adc_light();

/*
get_adc_value_light starts the conversion and returns ADCH.
ADCH contains the most significant 8 bits from the ADC value.
*/
uint8_t get_adc_value_light();

/*
read_sensor_temp initiates the init_adc_temp.
Then it stores, in the variable sensor_temp the value from the ADCH.
*/
int8_t read_sensor_light();
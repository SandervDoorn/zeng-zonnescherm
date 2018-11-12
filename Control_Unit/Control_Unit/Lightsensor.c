#include "Lightsensor.h"

void init_adc_light()
{
	// ref=Vcc, left adjust the result (8 bit resolution),
	// select channel 0 (PC1 = input)
	ADMUX = (1<<REFS0)|(1<<ADLAR)|(1<<0);
	// enable the ADC & prescale = 128
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint8_t get_adc_value_light()
{
	ADCSRA |= (1<<ADSC); // start conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADCH; // ms 8 bits
}

int8_t read_sensor_light()
{
	int sensor_light;
	init_adc_light();
	sensor_light = get_adc_value_light();
	return sensor_light;
	

}
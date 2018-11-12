#include "Temperaturesensor.h"


void init_adc_temp()
{
	// ref=Vcc, left adjust the result (8 bit resolution),
	// select channel 0 (PC1 = input)
	ADMUX = (1<<REFS0)|(1<<ADLAR);
	// enable the ADC & prescale = 128
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint8_t get_adc_value_temp()
{
	ADCSRA |= (1<<ADSC); // start conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADCH; // ms 8 bits
}

int8_t read_sensor_temp()
{
	int sensor_temp;
	float voltage;
	int8_t celsius;
	
	init_adc_temp();
	sensor_temp =  get_adc_value_temp();
	voltage = ((sensor_temp / 256.0)*5.015);
	celsius = ((voltage - 0.5) * 100);
	
	printf("Temp = %i", celsius);
	printf("\n");
	
	return celsius;
}

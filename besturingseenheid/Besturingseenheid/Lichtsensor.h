#define F_CPU 16E6
#include <avr/io.h>

void init_adc_light();
uint8_t get_adc_value_light();
int8_t read_sensor_light();
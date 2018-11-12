#include "Leds.h"

int16_t ths_temp; //get_ths_temp()
uint8_t ths_light; //get_ths_light
uint8_t ths_dist; //get_ths_dist
uint8_t ths_dist_min = 5;

int16_t celsius; //read_celsuis
uint8_t sensor_light; //read_light
uint8_t sensor_dist; //read_dist

void init_shutter()
{
	//set DDRB. PD 0 - PD 2 = output (leds).
	set_ths_dist(30);
	set_ths_light(150);
	set_ths_temp(26);
	set_shutter_mode(1);
	set_shutter_state(0);
	uint8_t arduino_name[20] = {'A','r','d','u','i','n','o'};
}


uint8_t moving()
{
	uint8_t opening_closing;
	if(ths_dist > sensor_dist & sensor_dist > ths_dist_min)
	{
		opening_closing = 1;
		//rolling out or in
	}
	else
	{
		opening_closing = 0;
		//stopped
	}
	return opening_closing;
}


void auto_regulator()
{
	static uint8_t light_set = 1;
	static uint8_t temp_set = 1;
	
	ths_temp = get_ths_temp(); //get_ths_temp()
	ths_light = get_ths_light(); //get_ths_light
	ths_dist = get_ths_dist(); //get_ths_dist
	
	// if moving is 0, check if readings are above or below the thresh holds. 
	if (moving() == 0)
	{
		if (sensor_light > ths_light)
		{
			light_set = 0;
		}
		if(sensor_light < (ths_light-25) & ~light_set)
		{
			light_set = 1;
		}
		if (celsius > ths_temp);
		{
			temp_set = 0;
		}
		if (celsius < (ths_temp - 2) & ~temp_set)
		{
			temp_set = 1;
		}
		
		/*
		if light sensor is higher than ths_light and celsius is higher than ths_temp.
		turn on red light = open
		*/
		if (light_set && temp_set)
		{
			PORTB = 4; //opgerold
		}
		
		else
		{
			PORTB = 1; //uitgerold
		}
	}
	else
	{
		PORTB ^= 2;
	}
}


// void moving()
// {
// 	uint8_t opening_closing;
// 	opening_closing = 1; // 1 = OPEN / OPENING, 0 = CLOSED / CLOSING
// 	//if(ths_dist > sensor_dist & sensor_dist > ths_dist_min)
// 	//while(opening_closing==1)
// 	//{
// 	if(opening_closing == 1)
// 	{	
// 		uint8_t x = read_sensor_dist();
// 		//Check distance sensor if still opening or fully open
// 		if(x < ths_dist)
// 		{
// 			PORTB ^= 4;
// 			//_delay_ms(1000);
// 		}
// 		if (x > ths_dist)
// 		{
// 			PORTB = 0;
// 			opening_closing = 0;
// 		}
// 		
// 
// 	}
// 	//}//whilend		
// }

// void auto_regulator()
// {
// 	static uint8_t light_set = 1;
// 	static uint8_t temp_set = 1;
// 	
// 	ths_temp = get_ths_temp(); //get_ths_temp()
// 	ths_light = get_ths_light(); //get_ths_light
// 	ths_dist = get_ths_dist(); //get_ths_dist
// 	
// 	// if moving is 0 =  if fully closed or opened, check if readings are above or below the thresholds. 
// 	
// 	//if sensor higher than threshold
// 	// Set light_set to 0 if True (If light_set 0, screen opens)
// 	if (sensor_light > ths_light)
// 	{
// 		light_set = 0;
// 	}
// 	//if sensor lower than ths and light isn't set
// 	if(sensor_light < (ths_light-25) && light_set==0)
// 	{
// 		light_set = 1;
// 	}
// 	if (celsius > ths_temp);
// 	{
// 		temp_set = 0;
// 	}
// 	if (celsius < (ths_temp - 2) && temp_set==0)
// 	{
// 		temp_set = 1;
// 	}
// 		
// 	/*
// 	if light sensor is higher than ths_light and celsius is higher than ths_temp.
// 	turn on red light = closed
// 	*/
// 	if (light_set && temp_set)
// 	{
// 		PORTB = 4; //PB2 = green light = closed
// 		set_shutter_state(0);
// 	}
// 		
// 	if (light_set == 0 || temp_set == 0)
// 	{
// 		PORTB = 1; //PB0 = red light = open
// 		set_shutter_state(1);
// 	}
// 	moving();
// }

// void manual_regulator()
// {
// 	//if closed
// 	//if (moving() == 0)
// 	{
// 		PORTB ^= 2;
// 	}
// 					
// }

void init_leds()
{
	DDRB = 0xFF;
	int mode;
	mode = get_shutter_mode(); //get_shutter_mode
	
	if (mode == 1)
	{
		celsius = read_sensor_temp(); //read_celsuis
		sensor_dist = read_sensor_dist(); //read_dist
		sensor_light = read_sensor_light(); //read_light
		auto_regulator();
	}
	else if (mode == 0)
	{
		sensor_dist = read_sensor_dist();
		//manual_regulator();
	}

}

#include "Temperaturesensor.h"
#include "Lightsensor.h"
#include "Distancesensor.h"
#include "Leds.h"
#include "serial.h"
#include "protocolhandeler.h"
#include "scheduler.h"

int main (void)
{
	init_dist();
	init_shutter();
	init_serial();
	
	SCH_Init_T1();
	
	SCH_Add_Task(init_leds, 0, 1000);
	SCH_Add_Task(read_command, 10, 1000);
	SCH_Start();
	
	while(1)
	{
		//SCH_Dispatch_Tasks();	
		init_leds();
		read_command();
		_delay_ms(500);
	}
	return 0;
}
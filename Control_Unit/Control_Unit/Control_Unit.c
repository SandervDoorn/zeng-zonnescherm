#include "Temperaturesensor.h"
#include "Lightsensor.h"
#include "Distancesensor.h"
#include "Leds.h"
#include "protocolhandeler.h"

int main (void)
{
	init_dist();
	init_serial();
	init_shutter();
	
	while(1)
	{
		read_command();
		init_leds();
		_delay_ms(1000);
	}
	return 0;
}
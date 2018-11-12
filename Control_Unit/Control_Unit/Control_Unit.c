#include "Temperaturesensor.h"
#include "Lightsensor.h"
#include "Distancesensor.h"
#include "Leds.h"
#include "serial.h"
#include "protocolhandeler.h"

int main (void)
{
	init_dist();
	init_shutter();
	init_serial();
	
	while(1)
	{
		init_leds();
		/*read_command();*/
		_delay_ms(1000);
	}
	return 0;
}
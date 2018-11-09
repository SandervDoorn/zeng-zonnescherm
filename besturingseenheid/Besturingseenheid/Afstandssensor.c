#include "Afstandssensor.h"
#include <stdio.h>
const uint8_t data = 0;
const uint8_t clock = 1;
const uint8_t strobe = 2;

void init_ports(void)
{
	//Set PORTB on output for display
	DDRB = 0xff;
		
	//Set PD0 (Trigger) to output and PD3 (Echo) to input
	DDRD = 0b00000100;
}

void init_timer(void)
// prescaling : max time = 2^16/16E6 = 4.1 ms, 4.1 >> 2.3, so no prescaling required
// normal mode, no prescale, stop timer
{
	TCCR1A = 0;
	TCCR1B = _BV(CS10);
}

void stop_timer()
{
	//Stop timer and reset value
	TCCR1B = 0;
	TCNT1 = 0;
}

void init_ext_int(void)
{
	// any change triggers ext interrupt 1
	EICRA = (1 << ISC10);
	EIMSK = (1 << INT1);
}

uint16_t calc_cm(uint16_t counter)
{
	/* First set cycles to uS and divide by 58 to get cm */
	return counter / 16 / 58;
}

void sendPulse()
{
	PORTD = 4;
	_delay_us(10);
	PORTD = (0<<PORTD0);
}

ISR (INT1_vect)
{	
	init_timer();
	while (bit_is_set(PIND, PD3))
	{
		//Wait for PIND to go back down, hence echo is finished
	}
	gv_counter = TCNT1;	
}
#include "Temperatuursensor.h"
#include "Lichtsensor.h"
#include "Afstandssensor.h"

#include <stdio.h>
#include <util/delay.h>

// serieel
// Getchar en putchar tbv. stdio.h
void ser_stdio_putchar(char c, FILE *stream) {
	if (c=='\n') {
		ser_transmit('\r');
	}
	ser_transmit(c);
}

FILE uart_output = FDEV_SETUP_STREAM(ser_stdio_putchar, NULL, _FDEV_SETUP_WRITE);

void ser_init() {
	// set the baud rate
	UBRR0H = 0;
	UBRR0L = 103;
	// disable U2X mode
	UCSR0A = 0;
	// enable TX and RX
	UCSR0B = _BV(TXEN0) | _BV(RXEN0);
	// set frame format : asynchronous, 8 data bits, 1 stop bit, no parity
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	// Setup stdout
	stdout=&uart_output;
}

// Low level transmit
void ser_transmit(uint8_t data) {
	// wait for an empty transmit buffer
	// UDRE is set when the transmit buffer is empty
	loop_until_bit_is_set(UCSR0A, UDRE0);
	// send the data
	UDR0 = data;
}

// Low level receive
uint8_t ser_receive() {
	loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
	return UDR0;
}

// Hele regel lezen
void ser_readln(char* buf, int maxlength, uint8_t echo) {
	int i=0;
	while(1) {
		uint8_t c = ser_receive();
		if (echo) ser_transmit(c);
		if (c=='\r') {
			if (echo) ser_transmit('\n');
			break; // ENTER ontvangen
			
		}
		if (i<maxlength-1) {
			buf[i++]=c;
		}
	}
	buf[i]='\0';
}

int main (void)
{
	init_ports();
	init_ext_int();
	ser_init;
	
	sei();
	
	
	ser_init();
	while(1)
	{	
		read_sensor_temp();
		sendPulse();
		stop_timer();
		uint8_t dist = (calc_cm(gv_counter));
		printf ("Distance = %i", dist);
		printf("\n\n"); 
		read_sensor_light();
		_delay_ms(1000);
		

	}
	return 0;
}
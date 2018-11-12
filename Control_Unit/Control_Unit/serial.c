/*
 * serial.c
 *
 * Created: 21-10-2018 13:22:56
 *  Author: Sander-Laptop
 */ 

#include "serial.h"

void init_serial() {
	//Setting baudrate
	UBRR0H = 0;
	UBRR0L = 103;
	
	UCSR0A = 0;
	
	//Set bits for RX and TX
	UCSR0B = _BV(TXEN0) | _BV(RXEN0);
	
	//Set frame: 8 databits and use 1 stopbit
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

void transmit_data(uint8_t data) {
	//Wait for transmit buffer to be empty
	loop_until_bit_is_set(UCSR0A, UDRE0);
	
	//Load new data into transmit buffer
	UDR0 = data;
}

void write_ser(char *data) {
	int i=0;
	
	//Loop until endline character is reached
	while (data[i]!='\0') {
		//Transmit character and go to next (i++)
		transmit_data(data[i++]);
	}
	//transmit newline character so readline() stops reading
	transmit_data('\n');
}

uint8_t receive_data() {
	//Wacht tot er data is
// 	int i = 0;
// 	
// 	while (!(UCSR0A & (1<<RXC0)) && i < 160000)
// 	{
// 		i++;
// 	}
// 	
// 	if (i==160000)
// 	{
// 		return '\r';
// 	}
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

//Copy from serial.c written by Simon van der Meer
void read_ser(char* buf, int maxlength) {
	int i=0;
	while(1) {
		uint8_t c = receive_data();
		
		//Bij een \r (ENTER) karakter uit de while loop gaan en \0 invoeren (einde string)
		if (c=='\r') {
			break; 
		}
		if (i<maxlength-1) {
			buf[i++]=c;
		}
	}
	buf[i]='\0';
}

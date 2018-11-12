/*
 * CFile1.h
 *
 * Created: 21-10-2018 14:13:56
 *  Author: Sander-Laptop
 */ 

#ifndef CFILE1_H_
#define CFILE1_H_

#define UBBRVAL = 103 //16.000.000(clockspeed)/16/9600(wanted baudrate)-1
#include <avr/io.h>
#include <stdio.h>

// void init_serial();
// 
// void transmit_data(uint8_t data);
// uint8_t receive_data();
// 
// void write_ser(char* data);
// void read_ser(char* buf, int maxlength);

void ser_stdio_putchar(char c, FILE *stream);
void ser_init();
void ser_transmit(uint8_t data);
uint8_t ser_receive();
void ser_readln(char* buf, int maxlength, uint8_t echo);

#endif /* CFILE1_H_ */
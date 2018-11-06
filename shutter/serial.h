/*
 * CFile1.h
 *
 * Created: 21-10-2018 14:13:56
 *  Author: Sander-Laptop
 */ 

#include <avr/io.h>
#ifndef CFILE1_H_
#define CFILE1_H_

void init_serial();

void transmit_data(uint8_t data);
uint8_t receive_data();

void write_ser(char* data);
void read_ser(char* buf, int maxlength);



#endif /* CFILE1_H_ */
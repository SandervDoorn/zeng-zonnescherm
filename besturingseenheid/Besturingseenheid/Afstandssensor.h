#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define HIGH 0x1
#define LOW 0x0

#define BEGIN 0x1
#define END 0x0

volatile uint16_t gv_counter; // 16 bit counter value
volatile uint8_t gv_echo; // a flag

void reset_display();
void working_distance(uint16_t dist);
void show_distance(uint16_t cm);
void sendCommand(uint8_t value);
void write(uint8_t pin, uint8_t val);
void shiftOut (uint8_t val);

void init_ports(void);
void init_timer(void);
void stop_timer();
void init_ext_int(void);
uint16_t calc_cm(uint16_t counter);
void sendPulse();
void init_dist();
int read_sensor_dist(void);
#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define HIGH 0x1
#define LOW 0x0

#define BEGIN 0x1
#define END 0x0

volatile uint16_t gv_counter; // 16 bit counter value
volatile uint8_t gv_echo; // a flag

/*
init_ports initiates the ports. 
PD2 for the trigger.
PD3 for the echo.
*/
void init_ports(void);

/*
init_times initiates the timer.
*/
void init_timer(void);

/*
stop_timer stops the timer.
*/
void stop_timer();

/*
init_ext_int triggers an interrupt on any change.
*/
void init_ext_int(void);

/*
calc_cm calculates the distance in cm based on uS.
*/
uint16_t calc_cm(uint16_t counter);

/*
sendPulse sends a pulse.
*/
void sendPulse();

/*
init_dist initiates the distance sensor based on the other inits.
*/
void init_dist();

/*
read_sensor_dist sends a pulse based on sendPulse.
Then stores calc_cm in dist.
*/
int read_sensor_dist(void);
/*
 * protocolhandeler.h
 *
 * Created: 6-11-2018 12:10:35
 *  Author: Sander-Laptop
 */ 


#ifndef PROTOCOLHANDELER_H_
#define PROTOCOLHANDELER_H_

char* get_name();
void set_name(char* val);
char* get_screen_state();
char* get_screen_mode();
char* get_thold_temp();
void set_thold_temp(char* val);
char* get_thold_dist();
char* get_sens_temp();
char* get_sens_light();
void read_command();





#endif /* PROTOCOLHANDELER_H_ */
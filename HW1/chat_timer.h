// chat_timer.h -- CP33357 assignment #1, Spring 2020
// includes functions returns current date & time & elapsed execution time
// S. U. Park, id #201624476, April 3rd, 2020

#ifndef _CHAT_TIMER_H_
#define _CHAT_TIMER_H_

//returns string contains local date (YYYY-mm-dd-day form)
void *get_local_date();

//returns string contains local time (hh-mm-ss form) 
void *get_local_time();

//returns string contains elapsed execution time (hh-mm-ss form)
void *get_elapsed_time();

#endif

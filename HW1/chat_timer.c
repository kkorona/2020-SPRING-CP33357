// chat_timer.c -- CP33357 assignment #1, Spring 2020
// includes functions returns current date & time & elapsed execution time
// S. U. Park, id #201624476, April 3rd, 2020

#include "chat_timer.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

const int BUFFER_SIZE = 80;                     // constant integer for buffer size
clock_t start_clock;                            // clock_t value, recorded when program execution starts
bool is_start_clock_not_initialized = false;    // ="start_clock isn't initialized"

//returns string contains local date (YYYY-mm-dd-day form)
void *get_local_date() {

    time_t      now;                    // current time_t value
    struct tm   time_data;              // localtime form of 'now'
    char        buffer[BUFFER_SIZE];    // buffer contains formatted local date
    char        *formatted_return;      // allocated string array of formatted date value, which is return value of this function

    // copy current time in 'now'
    time(&now);

    // format 'now' to localtime format
    time_data = *localtime(&now);
    
    // convert the local date to YYYY-mm-dd-day form and save it to buffer
    strftime(buffer, sizeof(buffer), "%Y-%m-%d-%a", &time_data);

    // generates allocated string for return
    formatted_return = malloc(sizeof(char) * BUFFER_SIZE);
    
    // copy buffer contents to return string
    strcpy(formatted_return, buffer);
    
    return formatted_return;
}

//returns string contains local time (hh-mm-ss form)
void *get_local_time() {

    time_t      now;                    // current time_t value
    struct tm   time_data;              // localtime form of 'now'
    char        buffer[BUFFER_SIZE];    // buffer contains formatted local time
    char        *formatted_return;      // allocated string array of formatted time value, which is return value of this function

    // copy current time in 'now'
    time(&now);

    // format 'now' to localtime format
    time_data = *localtime(&now);
    
    // convert the local date to hh-mm-ss form and save it to buffer
    strftime(buffer, sizeof(buffer), "%H-%M-%S", &time_data);

    // generates allocated string for return
    formatted_return = malloc(sizeof(char) * BUFFER_SIZE);
    
    // copy buffer contents to return string
    strcpy(formatted_return, buffer);
    
    return formatted_return;
}

//returns string contains elapsed execution time (hh-mm-ss form)
void *get_elapsed_time() {

    char        buffer[BUFFER_SIZE];     // buffer contains formatted elapsed execution time
    char        *formatted_return;       // allocated string array of elapsed execution time value, which is return value of this function

    // if start_clock isn't initialized, initialize it with the first call of clock() in this program.
    if(is_start_clock_not_initialized) {
        start_clock = clock();
        is_start_clock_not_initialized = false;
    }

    double elapsed_time =  (double)((clock() - start_clock)/CLOCKS_PER_SEC);    // clock_t value of elapsed execution time that transformed to second

    int hh = (int)elapsed_time / 3600; elapsed_time -= hh * 3600;   // calculate hour from elapsed execution time
    int mm = (int)elapsed_time / 60;   elapsed_time -= mm * 60;     // calculate minute from elapsed execution time
    int ss = (int)elapsed_time;                                      // calculate second from elapsed execution time
    
    // save hh-mm-ss form of elapsed execution time to buffer
    sprintf(buffer, "%d-%d-%d", hh,mm,ss);

    // generates allocated string for return
    formatted_return = malloc(sizeof(char) * BUFFER_SIZE);
    
    // copy buffer contents to return string
    strcpy(formatted_return, buffer);
    return formatted_return;
}

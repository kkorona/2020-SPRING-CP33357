#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

const int BUFFER_SIZE = 80;
clock_t start_clock;
bool is_start_clock_not_initialized = false;

void *get_local_date() {

    time_t      now;
    struct tm   time_data;
    char        buffer[BUFFER_SIZE];
    char        *formatted_return;

    time(&now);

    time_data = *localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d-%a", &time_data);

    formatted_return = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(formatted_return, buffer);
    return formatted_return;
}

void *get_local_time() {

    time_t      now;
    struct tm   time_data;
    char        buffer[BUFFER_SIZE];
    char        *formatted_return;

    time(&now);

    time_data = *localtime(&now);
    strftime(buffer, sizeof(buffer), "%H-%M-%S", &time_data);

    formatted_return = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(formatted_return, buffer);
    return formatted_return;
}

void *get_elapsed_time() {

    char        buffer[BUFFER_SIZE];
    char        *formatted_return;

    if(is_start_clock_not_initialized) {
        start_clock = clock();
        is_start_clock_not_initialized = false;
    }

    double elapsed_time =  (double)((clock() - start_clock)/CLOCKS_PER_SEC);

    int hh = (int)elapsed_time / 3600; elapsed_time -= hh * 3600;
    int mm = (int)elapsed_time / 60;   elapsed_time -= mm * 60;
    int ss = (int)elapsed_time;
    
    sprintf(buffer, "%d-%d-%d", hh,mm,ss);

    formatted_return = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(formatted_return, buffer);
    return formatted_return;
}

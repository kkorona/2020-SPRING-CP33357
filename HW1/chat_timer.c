#include <string.h>
#include <stdlib.h>
#include <time.h>

const int BUFFER_SIZE = 80;

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
    //return formatted_return;
    return buffer;
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
    // return formatted_return;
    return buffer;
}

void *get_elapsed_time() {

    time_t      now;
    struct tm   time_data;
    char        buffer[BUFFER_SIZE];
    char        *formatted_return;

    time(&now);

    time_data = *localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d-%a", &time_data);
    
    formatted_return = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(formatted_return, buffer);
    // return formatted_return;
    return buffer;
}

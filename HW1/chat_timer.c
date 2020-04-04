#include <chat_timer.h>

void *get_current_date() {

    time_t      now;
    struct tm   time_data;
    char        buffer[BUFFER_SIZE];
    char        *formatted_return;

    time(&now);

    ts = *localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d-%a");

    formatted_return = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(formatted_return, buffer);
    return formatted_return;
    
}

void *get_current_time() {

    time_t      now;
    struct tm   time_data;
    char        buffer[BUFFER_SIZE];
    char        *formatted_return;

    time(&now);

    ts = *localtime(&now);
    strftime(buffer, sizeof(buffer), "%H-%M-%S");

    formatted_return = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(formatted_return, buffer);
    return formatted_return;

}

void *get_elapsed_time() {

    time_t      now;
    struct tm   time_data;
    char        buffer[BUFFER_SIZE];
    char        *formatted_return;

    time(&now);

    ts = *localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d-%a");
    
    formatted_return = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(formatted_return, buffer);
    return formatted_return;
}

// main.c -- CP33357 assignment #1, Spring 2020
// S. U. Park, id #201624476, April 3rd, 2020

// preference.h -- header file contains initialized values for preference options of this program
#include "preference.h"

// chat_timer.h -- incldes functions returns current date & time & elapsed execution time
#include "chat_timer.h"

#include <pthread.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

WINDOW *local_date_wnd, *local_time_wnd, *elapsed_time_wnd;

void init() {
    initscr();
    local_date_wnd      = subwin( stdscr, LOCAL_DATE_VLINE,   LOCAL_DATE_HLINE,   LOCAL_DATE_VPOS,   LOCAL_DATE_HPOS   );
    local_time_wnd      = subwin( stdscr, LOCAL_TIME_VLINE,   LOCAL_TIME_HLINE,   LOCAL_TIME_VPOS,   LOCAL_TIME_HPOS   );
    elapsed_time_wnd    = subwin( stdscr, ELAPSED_TIME_VLINE, ELAPSED_TIME_HLINE, ELAPSED_TIME_VPOS, ELAPSED_TIME_HPOS );
    box( local_date_wnd,   '|', '-' );
    box( local_time_wnd,   '|', '-' );
    box( elapsed_time_wnd, '|', '-' );
}

void *update_text_on_screen( WINDOW *target_window, int vpos, int hpos, void* message ) {
    mvwprintw( target_window, vpos, hpos, (char*) message );
}

void *update_local_date_wnd() {
    // char* local_date_string = get_local_date();
    char* local_date_string = "LOCAL_DATE";
    update_text_on_screen( local_date_wnd, LOCAL_DATE_OUT_VPOS, LOCAL_DATE_OUT_HPOS, local_date_string ); 
}

void *update_local_time_wnd() {
    // char* local_time_string = get_local_time();
    char* local_time_string = "LOCAL_TIME";
    update_text_on_screen( local_time_wnd, LOCAL_TIME_OUT_VPOS, LOCAL_TIME_OUT_HPOS, local_time_string ); 
}

void *update_elapsed_time_wnd() {
    // char* elapsed_time_string = get_elapsed_time();
    char* elapsed_time_string = "ELAPSED_TIME";
    update_text_on_screen( elapsed_time_wnd, ELAPSED_TIME_OUT_VPOS, ELAPSED_TIME_OUT_HPOS, elapsed_time_string ); 
}

void run() {

    pthread_t   local_date_thread, local_time_thread, elapsed_time_thread;
    int         local_date_thread_return, local_time_thread_return, elapsed_time_thread_return;   

    while(1) {
        refresh();

        local_date_thread_return   = pthread_create(&local_date_thread,   NULL, update_local_date_wnd,   NULL);
        local_time_thread_return   = pthread_create(&local_time_thread,   NULL, update_local_time_wnd,   NULL);
        elapsed_time_thread_return = pthread_create(&elapsed_time_thread, NULL, update_elapsed_time_wnd, NULL);

        pthread_join(local_date_thread_return, NULL);
        pthread_join(local_time_thread_return, NULL);
        pthread_join(elapsed_time_thread_return, NULL);
    }

}

int main() {
    
    init(); // initialize screen prefernce with ncurses libs.
    run(); // run the main routine

    return 0;
}

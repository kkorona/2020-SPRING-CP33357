// main.c -- CP33357 assignment #1, Spring 2020
// main routine & thread controls of this program
// S. U. Park, id #201624476, April 3rd, 2020

// preference.h -- header file contains initialized values for preference options of this program
#include "preference.h"

// chat_timer.h -- incldes functions returns current date & time & elapsed execution time
#include "chat_timer.h"

#include <pthread.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

WINDOW *local_date_wnd, *local_time_wnd, *elapsed_time_wnd;     // subwindow of each timer

char* local_date_string = NULL, *local_time_string = NULL, *elapsed_time_string = NULL; // formatted output value of each timer

// initialize screen prefernce with ncurses.
void init() {
    
    // initialize stdscr of ncurses
    initscr();
    
    //generate & initialize subwindows for timers with size/position values in preference.h
    local_date_wnd      = subwin( stdscr, LOCAL_DATE_VLINE,   LOCAL_DATE_HLINE,   LOCAL_DATE_VPOS,   LOCAL_DATE_HPOS   );
    local_time_wnd      = subwin( stdscr, LOCAL_TIME_VLINE,   LOCAL_TIME_HLINE,   LOCAL_TIME_VPOS,   LOCAL_TIME_HPOS   );
    elapsed_time_wnd    = subwin( stdscr, ELAPSED_TIME_VLINE, ELAPSED_TIME_HLINE, ELAPSED_TIME_VPOS, ELAPSED_TIME_HPOS );
}

// update local_date_string with current local date
void *update_local_date() {
    
    // relase allocation of previous local date value
    if(local_date_string != NULL) {
         free(local_date_string);
    }
    
    // update the current local date
    local_date_string = get_local_date();
    return NULL;
}

// update local_time_string with current local time
void *update_local_time() {
    
    // relase allocation of previous local time value
    if(local_time_string != NULL) {
         free(local_time_string);
    }

    // update the current local time
    local_time_string = get_local_time();
    return NULL;
}

// update local_time_string with elapsed execution time
void *update_elapsed_time() {
    
    // relase allocation of previous local time value
    if(elapsed_time_string != NULL) {
         free(elapsed_time_string);
    }

    // update the elapsed execution time
    elapsed_time_string = get_elapsed_time();
    return NULL;

}

// main routine of this program
void run() {

    pthread_t   local_date_thread, local_time_thread, elapsed_time_thread;                          // pthread_t variables of each thread
    int         local_date_thread_return, local_time_thread_return, elapsed_time_thread_return;     // result values of each thread execution
    
    
    while(1) {
        
        // clear the screen
        clear();

        // draw borders of each timer window
        box( local_date_wnd,   '|', '-' );
        box( local_time_wnd,   '|', '-' );
        box( elapsed_time_wnd, '|', '-' );

        // allocate each timer update function to threads
        local_date_thread_return   = pthread_create(&local_date_thread,   NULL, update_local_date,   NULL);
        local_time_thread_return   = pthread_create(&local_time_thread,   NULL, update_local_time,   NULL);
        elapsed_time_thread_return = pthread_create(&elapsed_time_thread, NULL, update_elapsed_time, NULL);
        
        // join the threads
        pthread_join(local_date_thread, NULL);
        pthread_join(local_time_thread, NULL);
        pthread_join(elapsed_time_thread, NULL);


        // check errors of each return of thread
        // returns message under timer windows when error occured
        if(local_date_thread_return) {
            mvprintw(18, 2, " * error in local_date_thread   *");
        }
        if(local_time_thread_return) {
            mvprintw(19, 2, " * error in local_time_thread   *");
        }
        if(elapsed_time_thread_return) {
            mvprintw(20, 2, " * error in elaped_timee_thread *");
        }


        // prints the updated timer values on each subwindow
        mvwprintw(local_date_wnd, LOCAL_DATE_OUT_VPOS, LOCAL_DATE_OUT_HPOS, local_date_string);
        mvwprintw(local_time_wnd, LOCAL_TIME_OUT_VPOS, LOCAL_TIME_OUT_HPOS, local_time_string);
        mvwprintw(elapsed_time_wnd, ELAPSED_TIME_OUT_VPOS, ELAPSED_TIME_OUT_HPOS, elapsed_time_string);
        
        // refresh the screen
        refresh();
    }

}

int main() {
   
    // initialize screen prefernce with ncurses.
    init(); 
   
    // run the main routine
    run(); 

    return 0;
}

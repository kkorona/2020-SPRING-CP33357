// main.c -- CP33357 assignment #1, Spring 2020
// S. U. Park, id #201624476, April 3rd, 2020


// essentials.h -- includes essential header files for this program - ncurses.h
#include "essentials.h"

int main() {
    
    init(); // initialize screen prefernce with ncurses libs.
    run(); // run the main routine for timers.
    clearResources(); // release the allocated resources for this program.

    return 0;
}

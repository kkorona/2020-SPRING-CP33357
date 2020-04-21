// preference.h -- CP33357 assignment #1, Spring 2020
// header file contains initialized values for ncurses preference options of chat program
// S. U. Park, id #201624476, April 3rd, 2020

#ifndef PREFERENCE_H
#define PREFERENCE_H

// coordinate preference options for terminal window

const int TERMINAL_WINDOW_HLINE = 80;
const int TERMINAL_WINDOW_VLINE = 24;
const int TERMINAL_WINDOW_HPOS = 0;
const int TERMINAL_WINDOW_VPOS = 0;

// coordinate preference options for output window

const int OUTPUT_WINDOW_HLINE = 60;
const int OUTPUT_WINDOW_VLINE = 20;
const int OUTPUT_WINDOW_HPOS = 0;
const int OUTPUT_WINDOW_VPOS = 0;

// coordinate preference options for input window

const int INPUT_WINDOW_HLINE = 60;
const int INPUT_WINDOW_VLINE = 4;
const int INPUT_WINDOW_HPOS = 0;
const int INPUT_WINDOW_VPOS = 20;

// coordinate preference options for account logging window

const int ACCLOG_WINDOW_HLINE = 20;
const int ACCLOG_WINDOW_VLINE = 20;
const int ACCLOG_WINDOW_HPOS = 60;
const int ACCLOG_WINDOW_VPOS = 0;

// coordinate preference options for timer window

const int TIMER_WINDOW_HLINE = 20;
const int TIMER_WINDOW_VLINE = 4;
const int TIMER_WINDOW_HPOS = 60;
const int TIMER_WINDOW_VPOS = 20;

// coordinate preference options for local date timer

// determine width and heights
const int LOCAL_DATE_HLINE  = 20;
const int LOCAL_DATE_VLINE  = 1;
const int LOCAL_DATE_HPOS   = 60;
const int LOCAL_DATE_VPOS   = 21;
const int LOCAL_DATE_OUT_HPOS = 1;
const int LOCAL_DATE_OUT_VPOS = 0;

// coordinate preference options for local time timer

const int LOCAL_TIME_HLINE   = 15;
const int LOCAL_TIME_VLINE   = 5;
const int LOCAL_TIME_HPOS    = 1;
const int LOCAL_TIME_VPOS    = 1;
const int LOCAL_TIME_OUT_HPOS = 1;
const int LOCAL_TIME_OUT_VPOS = 0;


// coordinate preference options for local date timer

const int ELAPSED_TIME_HLINE = 15;
const int ELAPSED_TIME_VLINE = 5;
const int ELAPSED_TIME_HPOS  = 1;
const int ELAPSED_TIME_VPOS  = 2;
const int ELAPSED_TIME_OUT_HPOS = 1;
const int ELAPSED_TIME_OUT_VPOS = 0;

#endif

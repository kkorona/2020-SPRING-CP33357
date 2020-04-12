// preference.h -- CP33357 assignment #1, Spring 2020
// header file contains initialized values for preference options of this program
// S. U. Park, id #201624476, April 3rd, 2020

#ifndef PREFERENCE_H
#define PREFERENCE_H

// coordinate preference options for local date timer

// determine width and heights
const int LOCAL_DATE_HLINE  = 20;
const int LOCAL_DATE_VLINE  = 5;

// determine coordinate position in stdscr
const int LOCAL_DATE_VPOS   = 0;
const int LOCAL_DATE_HPOS   = 0;

// determine output position in local_date_wnd
const int LOCAL_DATE_OUT_HPOS = 2;
const int LOCAL_DATE_OUT_VPOS = 2;

// coordinate preference options for local time timer

// determine width and heights
const int LOCAL_TIME_HLINE   = 20;
const int LOCAL_TIME_VLINE   = 5;

// determine coordinate position in stdscr
const int LOCAL_TIME_VPOS    = 5;
const int LOCAL_TIME_HPOS    = 0;

// determine output position in local_time_wnd
const int LOCAL_TIME_OUT_HPOS = 2;
const int LOCAL_TIME_OUT_VPOS = 2;


// coordinate preference options for local date timer

// determine width and heights
const int ELAPSED_TIME_HLINE = 20;
const int ELAPSED_TIME_VLINE = 5;

// determine coordinate position in stdscr
const int ELAPSED_TIME_VPOS  = 10;
const int ELAPSED_TIME_HPOS  = 0;

// determine output position in elapsed_time_wnd
const int ELAPSED_TIME_OUT_HPOS = 2;
const int ELAPSED_TIME_OUT_VPOS = 2;

#endif

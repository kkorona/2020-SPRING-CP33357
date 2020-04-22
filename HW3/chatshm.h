// chatshm.h -- CP33357 assignment #2, Spring 2020
// includes multi chat structure and constraint constants
// S. U. Park, id #201624476, April 12nd, 2020

#ifndef __CHAT_SHM_M__
#define __CHAT_SHM_M__

// chat structure for multi chat with shared memory

typedef struct chatInfo {

    char userID[20];
    long messageTime;
    char message[40];

} CHAT_INFO;

typedef struct loginInfo {
    char userID[20];
    bool isON = false;
} LOGIN_INFO;


// target memory key constraint for assignment
const int CHAT_SHM_KEY = 20200406;
const int LOGIN_SHM_KEY = 20200407;

#endif //__CHAT_SHM_M__

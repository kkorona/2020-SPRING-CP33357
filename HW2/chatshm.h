#ifndef __CHAT_SHM_M__
#define __CHAT_SHM_M__

typedef struct chatInfo {

    char userID[20];
    long messageTime;
    char message[40];

} CHAT_INFO;

const int SHARED_MEMORY_KEY = 20200406;

#endif //__CHAT_SHM_M__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "chatshm.h"

int main() {
    int         shmid;
    CHAT_INFO   *chatInfo = NULL;

    void *shmaddr = (void*) 0;

    shmid = shmget((key_t)SHARED_MEMORY_KEY, sizeof(CHAT_INFO), 0666|IPC_CREAT|IPC_EXCL);

    if( shmid < 0 ) {
        
        shmid = shmget((key_t)SHARED_MEMORY_KEY, sizeof(CHAT_INFO), 0666);
        shmaddr = shmat(shmid, (void * )0, 0666);
        if(shmaddr < (void*) 0) {
            perror("shmat attatch is failed: ");
            exit(-1);
        }
    }
    else {
        shmaddr = shmat(shmid, (void*) 0, 0666);
    }
    chatInfo = (CHAT_INFO *) shmaddr;
    int lastUpdatedTime = 0;
    printf("--------- Chat Message -----------\n");
    while(1) {
        if(chatInfo->messageTime > lastUpdatedTime) {
            if(strcmp(chatInfo->message,"/bye\n") == 0) {
                printf("%s is out\n",chatInfo->userID);
            }
            else {
                printf("[%s]%ld: %s",
                    chatInfo->userID,
                    chatInfo->messageTime,
                    chatInfo->message);
            }
            lastUpdatedTime = chatInfo->messageTime;
        }
        
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "chatshm.h"

int main(int argc, char* argv[]) {
    int         shmid;
    char        userID[20];
    CHAT_INFO   *chatInfo = NULL;

    void *shmaddr = (void*) 0;

    if( argc < 2 ) {
        fprintf(stderr,"[Usage]: ./shmwrite USER_ID\n");
        exit(-1);
    }

    strcpy(userID, argv[1]);
    shmid = shmget((SHARED_MEMORY_KEY), sizeof(CHAT_INFO), 0666 | IPC_CREAT | IPC_EXCL);

    if( shmid < 0 ) {
        shmid = shmget((key_t)SHARED_MEMORY_KEY, sizeof(CHAT_INFO), 0666);
        shmaddr = shmat(shmid, (void*) 0, 0666);
        if( (int)shmaddr < 0) {
            perror("shmat attach is failed: ");
            exit(-1);
        }       
    }
    else {
        shmaddr = shmat(shmid, (void*) 0, 0666);
    }
    chatInfo = shmaddr;

    printf("--------- Chat Message -----------\n");
    while(1) {
        char inputstr[40];

        printf("Enter your message: ");
        fgets(inputstr, 40, stdin);
        strcpy(chatInfo->userID, userID);
        chatInfo->messageTime++;
        strcpy(chatInfo->message,inputstr); 

        if(!strcmp(chatInfo->message, "/bye\n")) {
            printf("%s is out\n", chatInfo->userID);
            break;
        }

        sleep(3);
    }

    return 0;
}

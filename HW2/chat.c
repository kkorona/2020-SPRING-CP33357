// chat.c -- CP33357 assignment #2, Spring 2020
// describes main routime for multi chat
// S. U. Park, id #201624476, April 12nd, 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// chatshm.h -- includes multi chat structure and constraint constants.
#include "chatshm.h"

int main(int argc, char* argv[]) {
    
    int         shmid;              // ID value of shared memory
    char        userID[20];         // ID of sender(a.k.a. user)
    CHAT_INFO*  chatInfo = NULL;   // pointer of chat information which will get the address of shared memory

    void *shmaddr = (void*) 0;      // address pointer of shared memory

    // if user didn't put username as argument, exit the program
    if( argc < 2 ) {
        fprintf(stderr,"[Usage]: ./chat USER_ID\n");
        exit(-1);
    }
    
    // renew username data
    strcpy(userID, argv[1]);
    
    // create shared memory for chat
    shmid = shmget((SHARED_MEMORY_KEY), sizeof(CHAT_INFO), 0666 | IPC_CREAT | IPC_EXCL);

    // if target shared memory already exists, get the shared memory id again
    if( shmid < 0 ) {
        
        // get shared memory for chat
        shmid = shmget((key_t)SHARED_MEMORY_KEY, sizeof(CHAT_INFO), 0666);
        
        // attach process to target shared memory
        shmaddr = shmat(shmid, (void*) 0, 0666);
        
        // if attach error occurs, exit the program
        if( (int)shmaddr < 0) {
            perror("shmat attach is failed: ");
            exit(-1);
        }       
    }
    else {
        shmaddr = shmat(shmid, (void*) 0, 0666);
    }
    
    // dereference shared memory space
    chatInfo = (CHAT_INFO*) shmaddr;

    printf("--------- Chat Message -----------\n");
    
    // main routine
    while(1) {
        
        char inputstr[40];      // user input    

        // get user input
        printf("Enter your message: ");
        fgets(inputstr, 40, stdin);

        // if user input is "..", print the shared memory data
        if(!strcmp(inputstr, "..\n")) {
            printf("[%s]%ld: %s", chatInfo->userID, chatInfo->messageTime, chatInfo->message);
        }

        // if user input is "/bye", exit the program
        else if(!strcmp(inputstr, "/bye\n")) {
            printf("%s is out\n", userID);
            break;
        }

        // user sends a message, update the shared memory data
        else {
            printf("SEND: [%s]: %s", userID, inputstr);
            strcpy(chatInfo->userID, userID);
            chatInfo->messageTime++;
            strcpy(chatInfo->message,inputstr); 
        }
    }

    return 0;
}

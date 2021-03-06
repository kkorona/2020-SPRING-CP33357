#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "chat.h"
#include "preference.h"
#include "chat_timer.h"
#include "chatshm.h"

WINDOW *input_scr;
WINDOW *chat_scr;
WINDOW *acclog_scr;
WINDOW *timer_scr;
WINDOW *local_date_wnd, *local_time_wnd, *elapsed_time_wnd;     // subwindow of each timer

char* local_date_string = NULL, *local_time_string = NULL, *elapsed_time_string = NULL; // formatted output value of each timer

int         chat_shmid;              // ID value of shared memory
int         login_shmid;
char        userID[20];         // ID of sender(a.k.a. user)
int         userIdx;
CHAT_INFO*  chat_logs = NULL;   // pointer of chat information which will get the address of shared memory
LOGIN_INFO*  login_logs = NULL;   // pointer of user login information which will get the address of shared memory
void *chat_shmaddr = (void*) 0;      // address pointer of chat shared memory
void *login_shmaddr = (void*) 0;      // address pointer of user login shared memory

void init_position() {
    input_scr = newwin(INPUT_WINDOW_VLINE, INPUT_WINDOW_HLINE, INPUT_WINDOW_VPOS, INPUT_WINDOW_HPOS);
    chat_scr = newwin(OUTPUT_WINDOW_VLINE, OUTPUT_WINDOW_HLINE, OUTPUT_WINDOW_VPOS, OUTPUT_WINDOW_HPOS);
    acclog_scr = newwin(ACCLOG_WINDOW_VLINE, ACCLOG_WINDOW_HLINE, ACCLOG_WINDOW_VPOS, ACCLOG_WINDOW_HPOS);
    timer_scr = newwin(TIMER_WINDOW_VLINE, TIMER_WINDOW_HLINE, TIMER_WINDOW_VPOS, TIMER_WINDOW_HPOS);
    
    // local date timer subwindow is temporarily deprecated.
    /*
    local_date_wnd      = subwin( timer_scr, LOCAL_DATE_VLINE,   LOCAL_DATE_HLINE,   LOCAL_DATE_VPOS,   LOCAL_DATE_HPOS   );
    local_time_wnd      = subwin( timer_scr, LOCAL_TIME_VLINE,   LOCAL_TIME_HLINE,   LOCAL_TIME_VPOS,   LOCAL_TIME_HPOS   );
    elapsed_time_wnd    = subwin( timer_scr, ELAPSED_TIME_VLINE, ELAPSED_TIME_HLINE, ELAPSED_TIME_VPOS, ELAPSED_TIME_HPOS );   
    */
    
    scrollok(chat_scr, TRUE);
    wprintw(chat_scr, "\n ***** Type /bye to quit!! ***** \n\n");
    wrefresh(chat_scr);
}

void init_chat_shm() {
    
    // create shared memory for chat
    chat_shmid = shmget((CHAT_SHM_KEY), sizeof(CHAT_INFO) * MAX_CHATS, 0666 | IPC_CREAT | IPC_EXCL);
    
    // if target shared memory already exists, attatch to target shared memory
    if( chat_shmid < 0 ) {
        
        // get shared memory for chat
        chat_shmid = shmget((key_t)CHAT_SHM_KEY, sizeof(CHAT_INFO) * MAX_CHATS, 0666);
        
        // attach process to target shared memory
        chat_shmaddr = shmat(chat_shmid, (void*) 0, 0666);
        
        // if attach error occurs, exit the program
        if( (int) chat_shmaddr < 0) {
            perror("shmat attach is failed: ");
            exit(-1);
        }       
    }
    else {
        chat_shmaddr = shmat(chat_shmid, (void*) 0, 0666);
    }
    
    // dereference shared memory space
    chat_logs = (CHAT_INFO*) chat_shmaddr;
}

void init_login_shm() {
    
    // create shared memory for chat
    login_shmid = shmget((LOGIN_SHM_KEY), sizeof(LOGIN_INFO) * MAX_USERS, 0666 | IPC_CREAT | IPC_EXCL);
    
    // if target shared memory already exists, attatch to target shared memory
    if( login_shmid < 0 ) {
        
        // get shared memory for chat
        login_shmid = shmget((key_t)LOGIN_SHM_KEY, sizeof(LOGIN_INFO) * MAX_USERS, 0666);
        
        // attach process to target shared memory
        login_shmaddr = shmat(login_shmid, (void*) 0, 0666);
        
        // if attach error occurs, exit the program
        if( (int) login_shmaddr < 0) {
            perror("shmat attach is failed: ");
            exit(-1);
        }       
    }
    else {
        login_shmaddr = shmat(login_shmid, (void*) 0, 0666);
    }
    
    // dereference shared memory space
    login_logs = (LOGIN_INFO*) login_shmaddr;
    for(int i=0; i<MAX_USERS; i++) {
        if(strcmp(login_logs[i].userID, userID) == 0) {
            login_logs[i].isON = 1;
            userIdx = i;
            break;
        }
        if(strcmp(login_logs[i].userID, "") == 0) {
            strcpy(login_logs[i].userID, userID);
            login_logs[i].isON = 1;
            userIdx = i;
            break;
        }
    }
}

void init_shm() {
    init_chat_shm();
    init_login_shm();
}

void remove_shm() {
    login_logs[userIdx].isON = 0;
    for(int i=0; i<MAX_USERS; i++) {
        if(login_logs[userIdx].isON) {
            return;
        }
    }
    if( chat_shmid < 0 ) {
        perror("shmget failed : ");
        exit(-1);
    }

    if(shmctl(chat_shmid, IPC_RMID, 0) < 0) {
        printf("Failed to delete shared memory\n");
        exit(-1);
    }
    else {
        printf("Successfully delete shared memory\n");
    }
    
    if(login_shmid < 0 ) {
        perror("shmget failed : ");
        exit(-1);
    }

    if(shmctl(login_shmid, IPC_RMID, 0) < 0) {
        printf("Failed to delete shared memory\n");
        exit(-1);
    }
    else {
        printf("Successfully delete shared memory\n");
    }
}

void run() {
    
    
    buff_in.id = 0;
    buff_out.id = 0;
    is_running = 1;
    
    pthread_t thread[5];
    
    pthread_create(&thread[0], NULL, get_input, NULL);
    pthread_create(&thread[1], NULL, print_chat, NULL);
    pthread_create(&thread[2], NULL, recv_send, NULL);
    pthread_create(&thread[3], NULL, update_time, NULL);
    pthread_create(&thread[4], NULL, log_account, NULL);
        
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    pthread_join(thread[2], NULL);
    pthread_join(thread[3], NULL);
    pthread_join(thread[4], NULL);
    
}

void *get_input() {
    char tmp[BUFFSIZE];
    // mvwhline(input_scr, 0, 0, 0, col);
    while(is_running) {
        mvwgetstr(input_scr, 1, 0, tmp);
        sprintf(buff_in.msg, "%s\n", tmp);
        if(strcmp(buff_in.msg, "/bye\n") == 0) {
            is_running = 0;
            break;
        }
        wprintw(chat_scr, "[Send: %d] > %s", buff_in.id, buff_in.msg);
        buff_in.id++;
        wrefresh(chat_scr);
        werase(input_scr);
        // mvwhline(input_scr, 0, 0, 0, col);
        wrefresh(input_scr);
        usleep(100);
    }
    return NULL;
}

void *print_chat() {
    char *msg;
    char buff[BUFFSIZE];
    
    struct message_buffer oldmsg;
    oldmsg.id = 0;
    
    while(is_running) {
        if(oldmsg.id != buff_out.id) {
            wprintw(chat_scr, buff_out.msg);
            oldmsg.id = buff_out.id;
            wrefresh(chat_scr);
        }
        
        usleep(100);
    }
    return NULL;
}

void *recv_send() {
    struct message_buffer oldmsg;
    oldmsg.id = 0;
    
    while(is_running) {
        memset(&(*buff_out.msg), 0, BUFFSIZE);
        sprintf(buff_out.msg, "[Recv: %d] %s\n", buff_out.id, "Chat Test");
        if(strcmp(buff_out.msg, "/bye\n") == 0) {
            fprintf(stderr, "Chat is closed\n");
            is_running = 0;
            break;
        }
        else {
            buff_out.id++;
        }
        sleep(3);
    }
    return NULL;
}

void *log_account() {
    int cnt = 1;
    char cntstr[100];
    while(is_running) {
        werase(acclog_scr);
        for(int i=0; i<MAX_USERS; i++) {
            if(login_logs[i].isON) {
                sprintf(cntstr, "%s\n", login_logs[i].userID);
                wprintw(acclog_scr, cntstr);
            }
        }
        wrefresh(acclog_scr);
        sleep(1);
    }
    return NULL;
}

void *update_time() {
    while(is_running) {
        // relase allocation of previous timer values
        
        // local date options is temporarily deprecated.
        /*
        if(local_date_string != NULL) {
             free(local_date_string);
        }
        */
        if(local_time_string != NULL) {
             free(local_time_string);
        }
        if(elapsed_time_string != NULL) {
             free(elapsed_time_string);
        }

        // update the current timer values
        /*
        local_date_string = get_local_date();
        */
        local_time_string = get_local_time();
        elapsed_time_string = get_elapsed_time();
        
        /*
        mvwprintw(local_date_wnd, LOCAL_DATE_OUT_VPOS, LOCAL_DATE_OUT_HPOS, local_date_string);
        mvwprintw(local_time_wnd, LOCAL_TIME_OUT_VPOS, LOCAL_TIME_OUT_HPOS, local_time_string);
        mvwprintw(elapsed_time_wnd, ELAPSED_TIME_OUT_VPOS, ELAPSED_TIME_OUT_HPOS, elapsed_time_string);
        */
        
        mvwprintw(timer_scr, LOCAL_TIME_VPOS, LOCAL_TIME_HPOS, local_time_string);
        mvwprintw(timer_scr, ELAPSED_TIME_VPOS, ELAPSED_TIME_HPOS, elapsed_time_string);
        wrefresh(timer_scr);
        usleep(500);
    }
    
    return NULL;
}

void *watch_state() {
    
}

void cleanup() {
    delwin(input_scr);
    delwin(chat_scr);
    delwin(acclog_scr);
    delwin(timer_scr);
    endwin();
}

void die(char *s) {
    delwin(input_scr);
    delwin(chat_scr);
    delwin(acclog_scr);
    delwin(timer_scr);
    endwin();
    perror(s);
    exit(-1);
}

int main(int argc, char* argv[]) {
    
    // if user didn't put username as argument, exit the program
    if( argc < 2 ) {
        fprintf(stderr,"[Usage]: ./chat USER_ID\n");
        exit(-1);
    }
    
    // renew username data
    strcpy(userID, argv[1]);
    
    initscr();
    
    getmaxyx(stdscr, row, col);
    
    init_shm();
    
    init_position();
        
    run();
    
    endwin();
    
    remove_shm();
    
    return 0;
}


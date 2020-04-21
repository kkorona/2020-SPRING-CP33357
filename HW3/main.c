#include "header.h"

WINDOW *input_scr;
WINDOW *chat_scr;

void chat() {
    input_scr = newwin(INPUT_WINDOW_H, col, row-INPUT_WINDOW_H, 0);
    chat_scr = newwin(row-INPUT_WINDOW_H, col, 0, 0,);
    
    scrollok(chat_scr, TRUE);
    wprintw(chat_scr, "\n ***** Type /exit to quit!! ***** \n\n");
    wrefresh(chat_scr);
    
    buff_in.id = 0;
    buff_out.id = 0;
    is_running = 1;
    
    pthread_t thread[3];
    
    pthread_create(&thread[0], NULL, get_input, NULL);
    pthread_create(&thread[1], NULL, print_chat, NULL);
    pthread_create(&thread[2], NULL, recv_send, NULL);
    
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    pthread_join(thread[2], NULL);
    
}

void *get_input() {
    char tmp[BUFFSIZE];
    mvwhline(input_scr, 0, 0, 0, col);
    while(is_running) {
        mvwgetstr(input_scr, 1, 0, tmp);
        sprintf(buff_in.msg, "%s\n", tmp);
        if(strcmp(buff_in.msg, "exit\n") == 0) {
            die("exit");
        }
        wprintw(chat_scr, "[Send: %d] > %s", buff_in.id, buff_in.msg);
        buff_in.id++;
        wrefresh(chat_scr);
        wrefresh(input_scr);
        mvwhline(chat_scr, 0, 0, 0, col);
        wrefresh(input_scr);
        usleep(100);
    }
}

void *print_chat() {
    while(is_running) {
    }
}

void *recv_send() {
    if (/exit) 
        is running = 0;
}

void cleanup() {
    delwin(input_scr);
    delwin(chat_scr);
    endwin();
}

void die(char *s) {
    delwin(input_scr);
    delwin(chat_scr);
    endwin();
    perror(s);
    exit(-1);
}

int main() {
    
    initscr();
    
    getmaxyx(stdscr, row, col);
    
    chat();
    
    endwin();
    
    return 0;
}
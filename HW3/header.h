#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>

#defind INPUT_WINDOW_H 2
#define BUFFSIZE 1024

int row;
int col;

struct message_buffer {
    char msg[BUFFSIZE];
    int id;
}

struct message_buffer buff_in;
struct message_buffer buff_out;

int is_running;

void chat();

void *print_chat();

void *get_input();

void *recv_send();

void cleanup();

void die(char *s);
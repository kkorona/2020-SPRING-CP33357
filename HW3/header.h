#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>

#define INPUT_WINDOW_H 2
#define BUFFSIZE 1024

int row;
int col;

struct message_buffer {
    char msg[BUFFSIZE];
    int id;
};

struct message_buffer buff_in;
struct message_buffer buff_out;

int is_running;

void chat();

void *get_input();

void *print_chat();

void *recv_send();

void *update_time();

void cleanup();

void die(char *s);
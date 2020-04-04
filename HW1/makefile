chat.out: main.o
    gcc -o chat.out main.o

main.o: chat_timer.o main.c preference.h
    gcc -c -o main.o main.c chat_timer.c

chat_timer.o : chat_timer.c chat_timer.h
    gcc -c -o chat_timer.o chat_timer.c

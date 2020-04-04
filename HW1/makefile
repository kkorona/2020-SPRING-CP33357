chat.out : main.o chat_timer.o
	gcc -o chat.out main.o chat_timer.o -lncurses -lpthread

main.o : main.c preference.h
	gcc -c -o main.o main.c 

chat_timer.o : chat_timer.c
	gcc -c -o chat_timer.o chat_timer.c

clean :
	rm *.o chat.out

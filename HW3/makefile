chat.out : chat.o chat_timer.o
	gcc -o chat.out chat.o chat_timer.o -lncurses -lpthread -wall

chat.o : chat.c
	gcc -c -o chat.o chat.c 

chat_timer.o : chat_timer.c chat_timer.h
	gcc -c -o chat_timer.o chat_timer.c

clean :
	rm *.o chat.out

chat.out : chat.o
	gcc -o chat.out chat.o -lncurses -lpthread

chat.o : chat.c
	gcc -c -o chat.o chat.c 

clean :
	rm *.o chat.out

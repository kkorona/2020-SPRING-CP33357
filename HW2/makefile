total: chat shmremove

chat: chat.c chatshm.h
	gcc -o chat chat.c -Wall

shmremove: shmremove.c chatshm.h
	gcc -o shmremove shmremove.c -Wall

clean:
	rm chat shmremove

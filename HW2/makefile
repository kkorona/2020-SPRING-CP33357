total: shmread shmwrite shmremove

shmread: shmread.c chatshm.h
	gcc -o shmread shmread.c

shmwrite: shmwrite.c chatshm.h
	gcc -o shmwrite shmwrite.c

shmremove: shmremove.c chatshm.h
	gcc -o shmremove shmremove.c

clean:
	rm shmread shmwrite shmremove

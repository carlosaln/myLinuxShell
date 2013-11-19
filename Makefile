CC = gcc
CFLAGS = -c

myshell:	myshell.o
	$(CC) myshell.o -o myshell

myshell.o:  myshell.c myshell.h
	$(CC) $(CFLAGS) myshell.c
	
clean:
	rm -f *.o myshell
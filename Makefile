# Makefile for gbemu

CC=gcc
CFLAGS=-Wall

makegbemu: main.c rom.c memory.c
	$(CC) $(CFLAGS) -o gbemu main.c rom.c memory.c

clean:
	rm -f *.o

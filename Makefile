# Makefile for gbemu

CC=gcc
CFLAGS=-Wall

makegbemu: main.c rom.c memory.c cpu.c registers.c
	$(CC) $(CFLAGS) -o gbemu main.c rom.c memory.c cpu.c registers.c

clean:
	rm -f *.o

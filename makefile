#-------------Makro-Part------------------
CC = gcc
CFLAGS = -Wall -std=c99 
LDFLAGs =
DEBUG = 


VPATH = src src/debug
#--------------Linker-Part-----------------
toy_cpu : main.o toy.o debug.o
	echo $@ is now linked
	$(CC) $(LDFLAGS) -o $@ $^
#--------------Compiler-Part---------------
main.o : main.c
	$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $<

toy.o : toy.c toy.h
	$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $<

debug.o : debug.c debug.h
	$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $<

clean : 
	rm -f *.o


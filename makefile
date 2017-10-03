#-------------Makro-Part------------------
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 
LDFLAGs =
DEBUG = -DNDEBUG 


VPATH = src
#--------------Linker-Part-----------------
toy_cpu : main.o toy.o helper.o
	echo $@ is now linked
	$(CC) $(LDFLAGS) -o $@ $^
#--------------Compiler-Part---------------
main.o : main.c
	$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $<

toy.o : toy.c toy.h
	$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $<

helper.o : helper.c helper.h
	$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $<

clean : 
	rm -f *.o coredump*.toy

#Makefile. You can make changes to this file according to your need
CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = problem2.o 

all: project

project: $(OBJS)


problem2.o: problem2.c
	$(CC) problem2.c -o p2

clean:
	rm -f *~ *.o project 
	

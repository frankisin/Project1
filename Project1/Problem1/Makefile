#Makefile. You can make changes to this file according to your need
CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = problem1.o

all: project

project: $(OBJS)


problem1.o: problem1.c
	$(CC) problem1.c -o p1

clean:
	rm -f *~ *.o project 
	

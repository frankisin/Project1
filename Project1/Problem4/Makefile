#Makefile. You can make changes to this file according to your need
CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = problem4.o

all: project

project: $(OBJS)

problem4.o: problem4.c
	$(CC) problem4.c -o p4
clean:
	rm -f *~ *.o project 
	

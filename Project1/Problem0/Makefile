#Makefile. You can make changes to this file according to your need
CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = problem0.o 

all: project

project: $(OBJS)

problem0.o: problem0.c
	$(CC) problem0.c -o p0
clean:
	rm -f *~ *.o project 
	

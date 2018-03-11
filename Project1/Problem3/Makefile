#Makefile. You can make changes to this file according to your need
CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = problem3.o 

all: project

project: $(OBJS)


problem3.o: problem3.c
	$(CC) problem3.c -o p3


clean:
	rm -f *~ *.o project 
	

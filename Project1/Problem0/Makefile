#Makefile. You can make changes to this file according to your need
CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = problem0.o problem1.o problem2.o problem3.o problem4.o

all: project

project: $(OBJS)

problem0.o: problem4.c
	$(CC) problem0.c -o p0

problem1.o: problem1.c
	$(CC) problem1.c -o p1

problem2.o: problem2.c
	$(CC) problem2.c -o p2

problem3.o: problem3.c
	$(CC) problem3.c -o p3

problem4.o: problem4.c
	$(CC) problem4.c -o p4
clean:
	rm -f *~ *.o project 
	

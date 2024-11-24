# makefile for A4 CIS2520 - Hamza Elmi
# target: dependencies...
#		gcc -Wall -std=c99 fileName.c
# Assignment 4 - due November 29

all: a4

a4: main.o graph_functions.o
	gcc -Wall -std=c99 -pedantic -o a4 main.o graph_functions.o

main.o: main.c graph.h
	gcc -Wall -std=c99 -pedantic -c main.c

graph_functions.o: graph_functions.c graph.h
	gcc -Wall -std=c99 -pedantic -c graph_functions.c

clean:
	rm -f *.o a4
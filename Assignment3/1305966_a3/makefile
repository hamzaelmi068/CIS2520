# makefile for A3 CIS2520 - Hamza Elmi
# target: dependencies...
#		gcc -Wall -std=c99 fileName.c
# Assignment 3 - due November 15

all: a3q1 a3q2

# Question 1
a3q1: a3q1_main.o a3q1_functions.o
	gcc -Wall -std=c99 -pedantic -o a3q1 a3q1_main.o a3q1_functions.o

a3q1_main.o: a3q1_main.c a3q1_header.h
	gcc -Wall -std=c99 -pedantic -c a3q1_main.c -o a3q1_main.o

a3q1_functions.o: a3q1_functions.c a3q1_header.h
	gcc -Wall -std=c99 -pedantic -c a3q1_functions.c -o a3q1_functions.o

# Question 2
a3q2: a3q2_main.o a3q2_functions.o
	gcc -Wall -std=c99 -pedantic -o a3q2 a3q2_main.o a3q2_functions.o

a3q2_main.o: a3q2_main.c a3q2_header.h
	gcc -Wall -std=c99 -pedantic -c a3q2_main.c -o a3q2_main.o

a3q2_functions.o: a3q2_functions.c a3q2_header.h
	gcc -Wall -std=c99 -pedantic -c a3q2_functions.c -o a3q2_functions.o

clean:
	rm -f *.o a3q1 a3q2
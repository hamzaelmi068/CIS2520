# makefile for A2 CIS2520 - Hamza Elmi
# target: dependencies...
#		gcc -Wall -std=c99 fileName.c

# Assignment 2 - due October 18 2024
all: a2q1 a2q2

# Question 1
a2q1: q1.o q1_functions.o 
	gcc -Wall -std=c99 -pedantic -o a2q1 q1.o q1_functions.o

q1.o: q1.c q1.h
	gcc -Wall -std=c99 -pedantic -c q1.c -o q1.o

q1_functions.o: q1_functions.c q1.h
	gcc -Wall -std=c99 -pedantic -c q1_functions.c -o q1_functions.o

# Question 2
a2q2: q2.o q2_functions.o
	gcc -Wall -std=c99 -pedantic -o a2q2 q2.o q2_functions.o

q2.o: q2.c q2.h
	gcc -Wall -std=c99 -pedantic -c q2.c -o q2.o

q2_functions.o: q2_functions.c q2.h
	gcc -Wall -std=c99 -pedantic -c q2_functions.c -o q2_functions.o

clean:
	rm -f *.o a2q1 a2q2
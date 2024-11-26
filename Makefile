###############################################################################
# File: Makefile
# Author: Mayumi Shimobe
# Date: November 26, 2024
# Description: Compile the predictive paging program and manage build targets.
# Note: 
###############################################################################

all: predictive_paging

predictive_paging: main.o matrix.o markov.o error_handling.o
	gcc -o predictive_paging main.o matrix.o markov.o error_handling.o

main.o: main.c matrix.h markov.h error_handling.h
	gcc -c main.c

matrix.o: matrix.c matrix.h error_handling.h
	gcc -c matrix.c

markov.o: markov.c markov.h matrix.h error_handling.h
	gcc -c markov.c

error_handling.o: error_handling.c error_handling.h
	gcc -c error_handling.c

clean:
	rm -f *.o predictive_paging

test:
	./predictive_paging test.txt

test_uniform:
	./predictive_paging test_uniform.txt

test_empty:
	./predictive_paging test_empty.txt

test_signle:
	./predictive_paging test_sigle.txt
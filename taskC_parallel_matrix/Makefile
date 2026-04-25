# Makefile for Parallel Matrix Adder

CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c99
LDFLAGS = -pthread

all: parallel_matrix

parallel_matrix: parallel_matrix.c
	$(CC) $(CFLAGS) -o parallel_matrix parallel_matrix.c $(LDFLAGS)

clean:
	rm -f parallel_matrix

.PHONY: all clean

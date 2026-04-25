# Makefile for Word Counter

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

all: word_counter

word_counter: word_counter.c
	$(CC) $(CFLAGS) -o word_counter word_counter.c

clean:
	rm -f word_counter

.PHONY: all clean

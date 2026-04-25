# Makefile for Multilevel Queue Scheduler

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: mlq_scheduler

mlq_scheduler: mlq_scheduler.c
	$(CC) $(CFLAGS) -o mlq_scheduler mlq_scheduler.c

clean:
	rm -f mlq_scheduler

.PHONY: all clean

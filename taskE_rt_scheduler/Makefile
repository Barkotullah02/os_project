# Makefile for Real-Time Scheduler

CC = gcc
CFLAGS = -Wall -Wextra -lm -std=c99
LDFLAGS = -lm

all: rt_scheduler

rt_scheduler: rt_scheduler.c
	$(CC) $(CFLAGS) -o rt_scheduler rt_scheduler.c $(LDFLAGS)

clean:
	rm -f rt_scheduler

.PHONY: all clean

# Makefile for Windows Elusive Cursor
# Requires MinGW or Visual Studio

CC = gcc
TARGET = elusive_cursor.exe
WINLIB = -luser32 -lgdi32 -lkernel32

all: $(TARGET)

$(TARGET): elusive_cursor.c
	$(CC) -o $(TARGET) elusive_cursor.c $(WINLIB)

clean:
	rm -f $(TARGET)

.PHONY: all clean

# Compiler
CC = g++

# Wall = enable compiler warnings
CFLAGS = -Wall

MAIN_INCLUDE = main.cpp Message.cpp
MAIN_EXECUTABLE = main

all: main

main:
	$(CC) $(CFLAGS) -o $(MAIN_EXECUTABLE) $(MAIN_INCLUDE)

clean:
	$(RM) $(MAIN_EXECUTABLE)

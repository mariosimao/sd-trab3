# Compiler
CC = g++

# Wall = enable compiler warnings
CFLAGS = -Wall

COORDINATOR_INCLUDE = coordinator.cpp Message.cpp Socket.cpp
COORDINATOR_EXECUTABLE = coordinator

PROCESS_INCLUDE = process.cpp Time.cpp Message.cpp Logger.cpp Socket.cpp
PROCESS_EXECUTABLE = process

all: coordinator process

coordinator:
	$(CC) $(CFLAGS) -o $(COORDINATOR_EXECUTABLE) $(COORDINATOR_INCLUDE)

process:
	$(CC) $(CFLAGS) -o $(PROCESS_EXECUTABLE) $(PROCESS_INCLUDE)

clean:
	$(RM) $(COORDINATOR_EXECUTABLE) $(PROCESS_EXECUTABLE)

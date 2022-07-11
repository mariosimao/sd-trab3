# Compiler
CC = g++

# Wall = enable compiler warnings
CFLAGS = -Wall -std=c++11 -ggdb

COORDINATOR_INCLUDE = coordinator.cpp Message.cpp Socket.cpp Logger.cpp MutualExclusion.cpp Time.cpp
COORDINATOR_EXECUTABLE = coordinator

PROCESS_INCLUDE = process.cpp Time.cpp Message.cpp Socket.cpp Logger.cpp
PROCESS_EXECUTABLE = process

all: coordinator process

coordinator:
	$(CC) $(CFLAGS) -o $(COORDINATOR_EXECUTABLE) $(COORDINATOR_INCLUDE)

process:
	$(CC) $(CFLAGS) -o $(PROCESS_EXECUTABLE) $(PROCESS_INCLUDE)

clean: clean-executables clean-logs free-port

clean-executables:
	$(RM) $(COORDINATOR_EXECUTABLE) $(PROCESS_EXECUTABLE)

clean-logs:
	$(RM) message.log resultado.txt

free-port:
	sudo fuser -k 8081/tcp

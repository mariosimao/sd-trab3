# Compiler
CC = g++

# Wall = enable compiler warnings
CFLAGS = -Wall -std=c++11 -ggdb

COORDINATOR_EXECUTABLE = coordinator
COORDINATOR_INCLUDE = $(wildcard ./src/Common/*.cpp) $(wildcard ./src/Server/*.cpp) -lpthread

PROCESS_EXECUTABLE = process
PROCESS_INCLUDE = $(wildcard ./src/Common/*.cpp) $(wildcard ./src/Client/*.cpp) -lpthread

all: coordinator process

coordinator:
	$(CC) $(CFLAGS) -o $(COORDINATOR_EXECUTABLE) $(COORDINATOR_EXECUTABLE).cpp $(COORDINATOR_INCLUDE)

process:
	$(CC) $(CFLAGS) -o $(PROCESS_EXECUTABLE) $(PROCESS_EXECUTABLE).cpp $(PROCESS_INCLUDE)

clean: clean-executables clean-logs free-port

clean-executables:
	$(RM) $(COORDINATOR_EXECUTABLE) $(PROCESS_EXECUTABLE)

clean-logs:
	$(RM) message.log resultado.txt

free-port:
	sudo fuser -k 8081/tcp

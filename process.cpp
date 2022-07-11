#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include "Time.h"
#include "Message.h"
#include "Logger.h"
#include "Socket.h"

void writeResult(int waitSeconds)
{
    std::ofstream resultFile;
    resultFile.open("resultado.txt", std::ios_base::app);

    int processId = getpid();
    std::string date = Time::now();

    resultFile << date << "\t" << processId << "\n";
    resultFile.close();

    sleep(waitSeconds);

    return;
}

int main(int argc, char const *argv[])
{
  try {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <k-seconds-to-wait> <r-repetitions>" << std::endl;
    exit(EXIT_FAILURE);
  }
  unsigned int kSeconds, rRepetitions;

  kSeconds = atoi(argv[1]);
  rRepetitions = atoi(argv[2]);

  Socket client = Socket::client(8081);
  int fd = client.getFd();
  pid_t processId = getpid();

  for (unsigned int i = 0; i < rRepetitions; i++) {
    Message request = Message::request(processId);
    Socket::sendMessage(fd, request);

    Message message;
    while (Socket::receiveMessage(fd, message)) {
        if (message.isGrant()) {
            break;
        };
    }

    writeResult(kSeconds);

    Message release = Message::release(processId);
    Socket::sendMessage(fd, release);
  }
  return 0;
  } catch(const char* error) {
    std::cerr << error << std::endl;
  }
}

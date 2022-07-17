#include <iostream>
#include <queue>
#include <unistd.h>
#include <thread>
#include <mutex>

#include "./src/Common/Message.h"
#include "./src/Common/Socket.h"
#include "./src/Server/CriticalSection.h"

void connection()
{

}

void criticalSection(int processId)
{

}

int terminal(CriticalSection &criticalSection)
{
  std::string command;

  while(true) {
    std::cout << "Please enter an valid command: 'queue', 'report' or 'exit'" << std::endl;
    getline(std::cin, command);
    if (command == "queue") {
      std::cout << "printing queue..." << std::endl;
      criticalSection.printQueue();
    }
    else if (command == "report")
    {
      std::cout << "printing report..." << std::endl;
    }
    else if (command == "exit")
    {
      return 0;
    }
    else
    {
      std::cerr << "Invalid command type. Use 'queue', 'report' or 'exit'." << std::endl;
    }
  }
}

void receiveConnections(CriticalSection &criticalSection, Logger &logger)
{
  auto onConnect = [&criticalSection, &logger](int newFd)
  {
    Message message;
    while (Socket::receiveMessage(newFd, message))
    {
      logger.log(message);

      pid_t processId = message.getProcessId();

      if (message.isRequest())
      {
        criticalSection.request(newFd, processId);
      }

      if (message.isRelease())
      {
        criticalSection.release();
      }
    }
    close(newFd);
  };

  try
  {
    Socket::server(8081, onConnect);
  }
  catch (const char *error)
  {
    std::cerr << error << std::endl;
  }
}

int main(int argc, char const *argv[])
{
  Logger logger("message.log");
  CriticalSection criticalSection(logger);

  std::thread interface(terminal, std::ref(criticalSection));
  std::thread connections(receiveConnections, std::ref(criticalSection), std::ref(logger));

  interface.join();
  connections.join();

  return 0;
}

#include <iostream>
#include <queue>
#include <unistd.h>
#include <thread>

#include "./src/Common/Message.h"
#include "./src/Common/Socket.h"
#include "./src/Server/MutualExclusion.h"

using namespace std;

std::queue<int> queue;

void connection()
{

}

void mutualExclusion(int processId)
{

}

int terminal()
{
  // print queue
  // print count of proccess allowed in rc, group by proccess id
  // end process

  string command;

  while(true) {
    cout << "Please enter an valid command: 'queue', 'report' or 'exit'" << endl;
    getline(cin, command);
    if (command == "queue") {
      cout << "printing queue..." << endl;
    }
    else if (command == "report")
    {
      cout << "printing report..." << endl;
    }
    else if (command == "exit")
    {
      return 0;
    }
    else
    {
      cerr << "Invalid command type. Use 'queue', 'report' or 'exit'." << endl;
    }
  }
}

void receiveConnections() {
  Logger logger("message.log");
  MutualExclusion mutualExclusion(logger);

  auto onConnect = [&mutualExclusion, &logger](int newFd)
  {
    Message message;
    while (Socket::receiveMessage(newFd, message))
    {
      logger.log(message);

      pid_t processId = message.getProcessId();

      if (message.isRequest())
      {
        mutualExclusion.request(newFd, processId);
      }

      if (message.isRelease())
      {
        mutualExclusion.release(newFd, processId);
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
  std::thread interface (terminal);
  std::thread connections (receiveConnections);

  interface.join();
  connections.join();

  return 0;
}

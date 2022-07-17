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

int terminal(MutualExclusion mutualExclusion)
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
      mutualExclusion.printQueue();
      // cout << "printing queue..." << endl;
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

void receiveConnections(MutualExclusion mutualExclusion, Logger logger)
{

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
        mutualExclusion.release();
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
  MutualExclusion mutualExclusion(logger);
  std::thread interface(terminal, std::ref(mutualExclusion));
  std::thread connections(receiveConnections, std::ref(mutualExclusion), std::ref(logger));

  interface.join();
  connections.join();

  return 0;
}

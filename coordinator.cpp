#include <iostream>
#include <queue>
#include <unistd.h>
#include "Message.h"



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


int main(int argc, char const *argv[])
{
    pid_t processId = getpid();
    Message message = Message::request(processId);
    std::cout << message.toString() << std::endl;

    Message m2 = Message::fromString("2|12345|00");
    std::cout << m2.toString() << std::endl;

    return terminal();
}

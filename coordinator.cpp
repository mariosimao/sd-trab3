#include <iostream>
#include <queue>
#include <unistd.h>
#include "Message.h"
#include "Socket.h"

std::queue<int> queue;

void connection()
{

}

void mutualExclusion(int processId)
{

}

void terminal()
{

}


int main(int argc, char const *argv[])
{
    // pid_t processId = getpid();
    // Message message = Message::request(processId);
    // std::cout << message.toString() << std::endl;

    // Message m2 = Message::fromString("2|12345|00");
    // std::cout << m2.toString() << std::endl;
    auto onConnect = [](int newFd) {
        Message m = Socket::receiveMessage(newFd);
        std::cout << m.toString() << std::endl;
    };

    Socket::server(8080, onConnect);
}

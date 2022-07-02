#include <iostream>
#include <unistd.h>
#include "Message.h"

using namespace std;

int main(int argc, char const *argv[])
{
    pid_t processId = getpid();
    Message message = Message::request(processId);
    std::cout << message.toString() << std::endl;

    Message m2 = Message::fromString("2|12345|00");
    std::cout << m2.toString() << std::endl;
}

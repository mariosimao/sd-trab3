#include "../Common/Socket.h"

#include "Lock.h"

Lock::Lock(int lockPort)
{
    Socket client = Socket::client(lockPort);

    this->socketFd = client.getFd();
    this->processId = getpid();
}

void Lock::acquire()
{
    Message request = Message::request(this->processId);
    Socket::sendMessage(this->socketFd, request);

    Message message;
    while (Socket::receiveMessage(this->socketFd, message)) {
        if (message.isGrant()) {
            break;
        };
    }

    return;
}

void Lock::release()
{
    Message release = Message::release(this->processId);
    Socket::sendMessage(this->socketFd, release);
}
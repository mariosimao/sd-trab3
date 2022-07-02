#ifndef SOCKET_H
#define SOCKET_H

#include <functional>
#include "Message.h"

class Socket
{
    private:
        int fd;
        Socket(int fd);
    public:
        static Socket server(int port, std::function<void(int)> onConnect);
        static Socket client(int serverPort);
        static Message receiveMessage(int fd);
        static void sendMessage(int fd, Message message);
        int getFd();
};

#endif
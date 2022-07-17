#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include "Socket.h"

Socket::Socket(int fd)
{
    this->fd = fd; // file descriptor
}

Socket Socket::server(int port, std::function<void(int)> onConnect)
{
    int socketFileDescriptor, newSocketFileDescriptor;
    struct sockaddr_in serverAddress, clientAddress;

    /**
     * Create socket
     *
     * AF_INET = IPV4
     * SOCK_STREAM = TCP
     * 0 = automatic protocol
     */
    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == 0) {
        throw strerror(errno);
    }

    // Setup server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Give socket the defined server address
    int bindResult = bind(
        socketFileDescriptor,
        (struct sockaddr *) &serverAddress,
        sizeof(serverAddress)
    );
    if (bindResult == -1) {
        throw strerror(errno);
    }

    int listenResult = listen(socketFileDescriptor, 1000);
    if (listenResult == -1) {
        throw strerror(errno);
    }

    socklen_t clientAddressLength = sizeof(clientAddress);

    while (1) {
        // Wait for socket connection
        newSocketFileDescriptor = accept(
            socketFileDescriptor,
            (struct sockaddr *) &clientAddress,
            &clientAddressLength
        );

        std::thread t(std::ref(onConnect), std::ref(newSocketFileDescriptor));
        t.detach();
    }

    close(socketFileDescriptor);
}

Socket Socket::client(int port)
{
    int socketFileDescriptor;
    struct sockaddr_in serverAddress;

    /**
     * Create socket
     *
     * AF_INET = IPV4
     * SOCK_STREAM = TCP
     * 0 = automatic protocol
     */
    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == 0) {
        throw strerror(errno);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) == -1) {
        throw strerror(errno);
    }

    int connectResult = connect(
        socketFileDescriptor,
        (struct sockaddr*) &serverAddress,
        sizeof(serverAddress)
    );
    if (connectResult == -1) {
        throw strerror(errno);
    }

    return Socket(socketFileDescriptor);
}

int Socket::receiveMessage(int fd, Message& message)
{
    char buffer[Message::SIZE];

    int read = recv(fd, buffer, sizeof(buffer), 0);
    if (read) {
        message = Message::fromString(buffer);
    }

    return read;
}

void Socket::sendMessage(int fd, Message message)
{
    send(fd, message.toString().c_str(), message.toString().length(), 0);
}

int Socket::getFd()
{
    return this->fd;
}

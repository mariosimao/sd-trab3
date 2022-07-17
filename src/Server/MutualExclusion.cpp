#include <queue>
#include <iostream>
#include "../Common/Socket.h"
#include "../Common/Message.h"

#include "MutualExclusion.h"

struct QueueItem;

MutualExclusion::MutualExclusion(Logger& logger): logger(logger)
{
}

void MutualExclusion::request(int fd, int processId)
{
    if (this->queue.empty()) {
        Message grant = Message::grant(processId);
        Socket::sendMessage(fd, grant);

        this->logger.log(grant);
    }

    QueueItem item = {processId,fd};

    this->queue.push(item);
}

void MutualExclusion::release(int fd, int processId)
{
    this->queue.pop();
    if (!this->queue.empty()) {
        fd = this->queue.front().fd;

        Message grant = Message::grant(processId);
        Socket::sendMessage(fd, Message::grant(processId));

        this->logger.log(grant);
    }
}

// std::queue<QueueItem> MutualExclusion::getQueue()
// {
//   return this->queue;
// }

// void print_queue()
// {
//   std::queue<QueueItem> queueToPrint;
//   while (!queueToPrint.empty())
//   {
//     int itemFd = queueToPrint.front().fd;
//     std::cout << itemFd << " ";
//     queueToPrint.pop();
//   }
//   std::cout << std::endl;
// }
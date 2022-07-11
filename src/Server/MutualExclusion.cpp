#include "../Common/Socket.h"
#include "../Common/Message.h"

#include "MutualExclusion.h"

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

    this->queue.push(fd);
}

void MutualExclusion::release(int fd, int processId)
{
    this->queue.pop();
    if (!this->queue.empty()) {
        fd = this->queue.front();

        Message grant = Message::grant(processId);
        Socket::sendMessage(fd, Message::grant(processId));

        this->logger.log(grant);
    }
}
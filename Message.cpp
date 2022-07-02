#include <vector>
#include "Message.h"

const int requestId = 1;
const int grantId = 2;
const int releaseId = 3;

Message::Message(int messageId, int processId)
{
    this->messageId = messageId;
    this->processId = processId;
}

Message Message::request(int processId)
{
    return Message(requestId, processId);
}

Message Message::grant(int processId)
{
    return Message(grantId, processId);
}

Message Message::release(int processId)
{
    return Message(releaseId, processId);
}

Message Message::fromString(std::string messageString)
{
    std::vector<int> ids;

    size_t pos = 0;
    std::string substring;
    while ((pos = messageString.find("|")) != std::string::npos) {
        substring = messageString.substr(0, pos);
        ids.push_back(std::stoi(substring));

        messageString.erase(0, pos + 1);
    }

    return Message(ids[0], ids[1]);
}

std::string Message::toString()
{
    char messageString[this->messageSize];
    sprintf(messageString, "%d|%d|", this->messageId, this->processId);

    std::string processIdString = std::to_string(this->processId);
    int processIdLength = processIdString.length();
    for (int i = 3 + processIdLength; i < this->messageSize; i++) {
        messageString[i] = '0';
    }

    messageString[this->messageSize] = '\0';

    return messageString;
}

bool Message::isRequest()
{
    return this->messageId == requestId;
}

bool Message::isGrant()
{
    return this->messageId == grantId;
}

bool Message::isRelease()
{
    return this->messageId == releaseId;
}

int Message::getProcessId()
{
    return this->processId;
}

std::string Message::getTypeName()
{
    if (this->messageId == requestId) {
        return "REQUEST";
    }

    if (this->messageId == grantId) {
        return "GRANT";
    }

    if (this->messageId == releaseId) {
        return "RELEASE";
    }

    return "UNDEFINED";
}
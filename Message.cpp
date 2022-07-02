#include <vector>
#include "Message.h"

Message::Message(int messageId, int processId)
{
    this->messageId = messageId;
    this->processId = processId;
}

Message Message::request(int processId)
{
    int messageId = 1;

    return Message(messageId, processId);
}

Message Message::grant(int processId)
{
    int messageId = 2;

    return Message(messageId, processId);
}

Message Message::release(int processId)
{
    int messageId = 3;

    return Message(messageId, processId);
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

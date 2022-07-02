#include <vector>
#include "Message.h"

const int Message::SIZE = 10;
const int Message::REQUEST_ID = 1;
const int Message::GRANT_ID = 2;
const int Message::RELEASE_ID = 3;

Message::Message(int messageId, int processId)
{
    this->messageId = messageId;
    this->processId = processId;
}

Message Message::request(int processId)
{
    return Message(Message::REQUEST_ID, processId);
}

Message Message::grant(int processId)
{
    return Message(Message::GRANT_ID, processId);
}

Message Message::release(int processId)
{
    return Message(Message::RELEASE_ID, processId);
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
    char messageString[Message::SIZE];
    sprintf(messageString, "%d|%d|", this->messageId, this->processId);

    std::string processIdString = std::to_string(this->processId);
    int processIdLength = processIdString.length();
    for (int i = 3 + processIdLength; i < Message::SIZE; i++) {
        messageString[i] = '0';
    }

    messageString[Message::SIZE] = '\0';

    return messageString;
}

bool Message::isRequest()
{
    return this->messageId == Message::REQUEST_ID;
}

bool Message::isGrant()
{
    return this->messageId == Message::GRANT_ID;
}

bool Message::isRelease()
{
    return this->messageId == Message::RELEASE_ID;
}

int Message::getProcessId()
{
    return this->processId;
}

std::string Message::getTypeName()
{
    if (this->messageId == Message::REQUEST_ID) {
        return "REQUEST";
    }

    if (this->messageId == Message::GRANT_ID) {
        return "GRANT";
    }

    if (this->messageId == Message::RELEASE_ID) {
        return "RELEASE";
    }

    return "UNDEFINED";
}
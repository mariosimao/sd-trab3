#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message
{
    private:
        const int messageSize = 10;
        int messageId;
        int processId;
        Message(int messageId, int processId);
    public:
        static Message request(int processId);
        static Message grant(int processId);
        static Message release(int processId);
        static Message fromString(std::string message);
        std::string toString();
        bool isRequest();
        bool isGrant();
        bool isRelease();
        int getProcessId();
        std::string getTypeName();
};

#endif
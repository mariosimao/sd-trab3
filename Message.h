#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message
{
    private:
        static const int REQUEST_ID, GRANT_ID, RELEASE_ID;
        int messageId;
        int processId;
        Message(int messageId, int processId);
    public:
        static const int SIZE;
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
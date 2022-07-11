#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message
{
    private:
        static const int REQUEST_ID, GRANT_ID, RELEASE_ID;
        int messageId;
        pid_t processId;
        Message(int messageId, pid_t processId);
    public:
        static const int SIZE;
        Message();
        static Message request(pid_t processId);
        static Message grant(pid_t processId);
        static Message release(pid_t processId);
        static Message fromString(std::string message);
        std::string toString();
        bool isRequest();
        bool isGrant();
        bool isRelease();
        pid_t getProcessId();
        std::string getTypeName();
};

#endif
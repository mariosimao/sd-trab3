#ifndef LOCK_H
#define LOCK_H

#include <unistd.h>

class Lock
{
    private:
        int socketFd;
        pid_t processId;
    public:
        Lock(int lockPort);
        void acquire();
        void release();
};

#endif
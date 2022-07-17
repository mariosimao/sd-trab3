#ifndef CRITICAL_SECTION_H
#define CRITICAL_SECTION_H

#include <queue>
#include "Logger.h"

class CriticalSection
{
    struct QueueItem
    {
        int processId;
        int fd;
    };

    private:
        std::deque<QueueItem> queue;
        Logger &logger;
    public:
        CriticalSection(Logger &logger);
        void request(int fd, int processId);
        void release();
        void printQueue();
};

#endif
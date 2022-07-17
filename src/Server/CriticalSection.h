#ifndef CRITICAL_SECTION_H
#define CRITICAL_SECTION_H

#include <queue>
#include <map>
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
        std::map<int, int> report;
        void addToReport(int processId);
    public :
        CriticalSection(Logger &logger);
        void request(int fd, int processId);
        void release();
        void printQueue();
        void printReport();
};

#endif
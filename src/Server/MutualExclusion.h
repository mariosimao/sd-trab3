#ifndef MUTUAL_EXCLUSION_H
#define MUTUAL_EXCLUSION_H

#include <queue>
#include "Logger.h"

class MutualExclusion
{
    struct QueueItem
    {
        int processId;
        int fd;
    };

    private:
        std::queue<QueueItem> queue;
        Logger &logger;
    public:
        MutualExclusion(Logger &logger);
        void request(int fd, int processId);
        void release(int fd, int processId);
        // std::queue<QueueItem> getQueue();
};

#endif
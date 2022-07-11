#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include "Message.h"

class Logger
{
    private:
        std::string filename;
    public:
        Logger(std::string filename);
        void log(Message message);
};

#endif
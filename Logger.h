#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include "Message.h"

class Logger
{
    public:
        static void log(Message message);
};

#endif
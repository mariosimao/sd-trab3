#include <fstream>

#include "Time.h"
#include "Logger.h"

Logger::Logger(std::string filename)
{
    this->filename = filename;
}

void Logger::log(Message message)
{
    std::string date = Time::now();
    std::string messageType = message.getTypeName();
    int processId = message.getProcessId();

    std::ofstream file;
    file.open(this->filename, std::ios_base::app);

    file << date << "\t" << messageType << "\t" << processId << "\n";

    file.close();

    return;
}

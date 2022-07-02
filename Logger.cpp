#include <fstream>
#include "Time.h"
#include "Logger.h"

void Logger::log(Message message)
{
    std::ofstream file;
    file.open("message.log", std::ios_base::app);

    std::string date = Time::now();
    std::string messageType = message.getTypeName();
    int processId = message.getProcessId();

    file << date << "\t" << messageType << "\t" << processId << "\n";
    file.close();

    return;
}

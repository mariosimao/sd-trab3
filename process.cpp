#include <fstream>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include "Time.h"
#include "Message.h"
#include "Logger.h"

void writeResult(int waitSeconds)
{
    std::ofstream resultFile;
    resultFile.open("resultado.txt", std::ios_base::app);

    int processId = getpid();
    std::string date = Time::now();

    resultFile << date << "\t" << processId << "\n";
    resultFile.close();

    sleep(waitSeconds);

    return;
}

int main(int argc, char const *argv[])
{
    writeResult(1);
    writeResult(1);
    writeResult(1);
    writeResult(1);
    writeResult(1);

    // auto m1 = Message::request(1234);
    // auto m2 = Message::grant(1234);
    // auto m3 = Message::release(1234);

    // Logger::log(m1);
    // sleep(1);
    // Logger::log(m2);
    // Logger::log(m3);
    // Logger::log(m1);
    // Logger::log(m2);
    // Logger::log(m3);
}


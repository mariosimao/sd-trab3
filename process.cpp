#include <iostream>
#include <fstream>
#include <unistd.h>

#include "src/Common/Time.h"
#include "src/Common/Message.h"
#include "src/Common/Socket.h"

#include "src/Client/Lock.h"

#define LOCK_PORT 8081

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
    unsigned int kSeconds, rRepetitions;

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <k-seconds-to-wait> <r-repetitions>" << std::endl;
        exit(EXIT_FAILURE);
    }

    kSeconds = atoi(argv[1]);
    rRepetitions = atoi(argv[2]);

    Lock lock(LOCK_PORT);

    for (unsigned int i = 0; i < rRepetitions; i++) {
        lock.acquire();
        writeResult(kSeconds);
        lock.release();
    }

    return 0;
}

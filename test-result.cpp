#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <map>

struct ResultLine {
    std::string timestamp;
    int processId;
};

std::vector<ResultLine> parseResult(std::string filename)
{
    std::ifstream resultFile;
    resultFile.open(filename);

    std::string line;
    std::vector<ResultLine> result;
    while (std::getline(resultFile, line)) {
        std::string lineValue;
        std::vector<std::string> lineValues;

        // Split string with '\t' delimiter
        std::stringstream lineStream(line);
        while(std::getline(lineStream, lineValue, '\t')) {
            lineValues.push_back(lineValue);
        }

        ResultLine resultLine = {
            lineValues[0],
            atoi(lineValues[1].c_str())
        };

        result.push_back(resultLine);
    }

    resultFile.close();

    return result;
}

void testNumberOfLines(
    std::vector<ResultLine> result,
    unsigned int nProcesses,
    unsigned int rRepetitions
) {
    unsigned int expectedSize = nProcesses * rRepetitions;

    assert(expectedSize == result.size());
}

void testClockOrder(std::vector<ResultLine> result)
{
    std::string previousTimestamp;
    for (size_t i = 0; i < result.size(); i++) {
        std::string currentTimestamp = result[i].timestamp;
        assert(currentTimestamp >= previousTimestamp);

        previousTimestamp = currentTimestamp;
    }
}

void testRepetitions(std::vector<ResultLine> result, unsigned int rRepetitions)
{
    std::map<int, unsigned int> countByProcess;

    for (size_t i = 0; i < result.size(); i++) {
        int processId = result[i].processId;

        if (countByProcess.find(processId) == countByProcess.end()) {
            countByProcess[processId] = 1;
        } else {
            countByProcess[processId]++;
        }
    }

    for (auto it = countByProcess.begin(); it != countByProcess.end(); ++it) {
        unsigned int count = it->second;

        assert(count == rRepetitions);
    }
}

int main(int argc, char *argv[])
{
    unsigned int nProcesses, rRepetitions;

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <n-processes> <r-repetitions>" << std::endl;
        exit(EXIT_FAILURE);
    }

    nProcesses = atoi(argv[1]);
    rRepetitions = atoi(argv[2]);

    std::vector<ResultLine> result = parseResult("resultado.txt");

    testNumberOfLines(result, nProcesses, rRepetitions);
    testClockOrder(result);
    testRepetitions(result, rRepetitions);
}

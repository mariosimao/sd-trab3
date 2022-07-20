#include <sstream>
#include <iomanip>
#include <chrono>

#include "Time.h"

std::string Time::now()
{
    tm localTime;
    std::stringstream buffer;

    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    time_t now = std::chrono::system_clock::to_time_t(t);
    localtime_r(&now, &localTime);

    const std::chrono::duration<double> tse = t.time_since_epoch();
    std::chrono::seconds::rep milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count() % 1000;

    buffer << (1900 + localTime.tm_year) << '-'
        << std::setfill('0') << std::setw(2) << (localTime.tm_mon + 1) << '-'
        << std::setfill('0') << std::setw(2) << localTime.tm_mday << ' '
        << std::setfill('0') << std::setw(2) << localTime.tm_hour << ':'
        << std::setfill('0') << std::setw(2) << localTime.tm_min << ':'
        << std::setfill('0') << std::setw(2) << localTime.tm_sec << '.'
        << std::setfill('0') << std::setw(3) << milliseconds;

    return buffer.str();
}
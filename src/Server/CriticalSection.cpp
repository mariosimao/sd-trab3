#include <iostream>
#include <iomanip>
#include <mutex>

#include "../Common/Socket.h"
#include "../Common/Message.h"

#include "CriticalSection.h"

std::mutex mutex;

CriticalSection::CriticalSection(Logger& logger): logger(logger)
{
}

void CriticalSection::request(int fd, int processId)
{
    mutex.lock();
    if (this->queue.empty()) {
        Message grant = Message::grant(processId);
        Socket::sendMessage(fd, grant);
        addToReport(processId);
        this->logger.log(grant);
    }

    QueueItem item = {processId,fd};

    this->queue.push_back(item);
    mutex.unlock();
}

void CriticalSection::release()
{
    mutex.lock();
    this->queue.pop_front();
    if (!this->queue.empty()) {
        int fd = this->queue.front().fd;
        int processId = this->queue.front().processId;

        Message grant = Message::grant(processId);
        Socket::sendMessage(fd, grant);
        addToReport(processId);
        this->logger.log(grant);
    }
    mutex.unlock();
}

void CriticalSection::printQueue()
{
    mutex.lock();
    size_t size = this->queue.size();
    std::cout << "Size: " << size << " | Items: ";

    for (size_t i = 0; i < size; i++) {
        QueueItem item = this->queue.at(i);
        std::cout << item.processId << " ";
    }
    std::cout << std::endl;
    mutex.unlock();
}

void CriticalSection::addToReport(int processId)
{
  if (this->report.find(processId) == this->report.end())
  {
    this->report[processId] = 1;
  }
  else
  {
    this->report[processId]++;
  }
}

void CriticalSection::printReport()
{
  int colWidth = 15;

  // table header
  std::cout << std::setfill('*') << std::setw(2 * colWidth) << "*" << std::endl;
  std::cout << std::setfill(' ') << std::fixed;
  std::cout << std::setw(colWidth) << "ProcessId" << std::setw(colWidth) << "access count" << std::endl;
  std::cout << std::setfill('*') << std::setw(2 * colWidth) << "*" << std::endl;

  // create table data
  std::map<int, int>::iterator it;
  for (it = this->report.begin(); it != this->report.end(); ++it)
  {
    std::cout << std::setfill(' ') << std::setw(colWidth) << it->first << std::setw(colWidth) << it->second << std::endl;
  }
}
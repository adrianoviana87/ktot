#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "ktot/domain/task_t.h"
#include "ktot/domain/task_service_t.h"
#include "ktot/repo_json/task_json_repository_t.h"

#include <chrono>
#include <ratio>
#include <ctime>
#include <iomanip>

using namespace std::chrono_literals;

template<typename Clock, typename Duration>
std::ostream &operator<<(std::ostream &stream,
  const std::chrono::time_point<Clock, Duration> &time_point) {
  const time_t time = Clock::to_time_t(time_point);
#if __GNUC__ > 4 || \
    ((__GNUC__ == 4) && __GNUC_MINOR__ > 8 && __GNUC_REVISION__ > 1)
  // Maybe the put_time will be implemented later?
  struct tm tm;
  localtime_r(&time, &tm);
  return stream << std::put_time(&tm, "%c"); // Print standard date&time
#else
  char buffer[26];
  ctime_r(&time, buffer);
  buffer[24] = '\0';  // Removes the newline that is added
  return stream << buffer;
#endif
}

void printTask(const ktot::task_t& task)
{
  std::cout << "Task (" << task.id() << "): " << task.name() << std::endl;
  std::cout << "Works:" << std::endl;
  for (auto work : task.works())
  {
    std::cout << "Started at: " << work.startedAt() << std::endl;
    std::cout << "Ended at: " << work.endedAt() << std::endl;
  }
}

int main()
{
  ktot::task_service_t service = { std::make_shared<ktot::task_json_repository_t>() };
  std::string id;
  std::cout << "Type the id to read: ";
  std::cin >> id;
  auto foundTask = service.get(id);
  if (foundTask)
  {
    printTask(*foundTask);
  }
  else
  {
    std::cout << "Task not found!" << std::endl;
  }

  // ktot::task_t task = { "My task" };
  // auto now = std::chrono::system_clock::now();
  // task.works({ { now, now + 10s }, { now + 20s, now + 40s } });
  // service.save(task);
  // printTask(task);

  return 0;
}

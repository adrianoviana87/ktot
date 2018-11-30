#include "ktot/domain/task_service_t.h"

#include <algorithm>

namespace ktot
{
  task_service_t::task_service_t(task_repository_ptr repository)
    : m_repository(repository)
  {
  }

  std::string task_service_t::save(task_ptr task)
  {
    m_repository->save(task);
    return task->id();
  }

  std::vector<task_ptr> task_service_t::list()
  {
    return m_repository->list();
  }

  task_ptr task_service_t::get(std::string id)
  {
    return m_repository->get(id);
  }

  task_ptr task_service_t::find_by_name(const std::string& task_name)
  {
    auto tasks = list();
    auto it = std::find_if(
      std::begin(tasks),
      std::end(tasks),
      [&](auto& t)
      {
        return t->name() == task_name;
      });

    if (it != std::end(tasks))
    {
      return *it;
    }

    return nullptr;
  }

  task_ptr task_service_t::start_by_name(const std::string& task_name)
  {
    end_all();
    auto found_task = find_by_name(task_name);
    if (!found_task)
    {
      found_task = std::make_shared<task_t>(task_name);
    }

    found_task->start();

    return found_task;
  }

  void task_service_t::end_all()
  {
    auto tasks = list();
    for (auto& task : tasks)
    {
      if(task->finish_incomplete())
      {
        save(task);
      }
    }
  }
}

#include "ktot/domain/task_service_t.h"

namespace ktot
{
  task_service_t::task_service_t(std::shared_ptr<task_repository_t> repository)
    : m_repository(repository)
  {
  }

  std::string task_service_t::save(task_t& task)
  {
    m_repository->save(task);
    return task.id();
  }

  std::vector<task_t> task_service_t::list()
  {
    return m_repository->list();
  }

  std::optional<task_t> task_service_t::get(std::string id)
  {
    return m_repository->get(id);
  }
}

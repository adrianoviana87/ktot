#pragma once
#include <memory>
#include <vector>
#include <string>
#include "ktot/domain/task_repository_t.h"

namespace ktot
{
  class task_service_t
  {
    public:
      task_service_t(task_repository_ptr repository);

      std::string save(task_ptr task); 
      std::vector<task_ptr> list();
      task_ptr get(std::string id);

      task_ptr start_by_name(const std::string& task_name);
      void end_all();
    private:
      task_ptr find_by_name(const std::string& task_name);
      task_repository_ptr m_repository;
  };

  using task_service_ptr =
    std::shared_ptr<task_service_t>;
}

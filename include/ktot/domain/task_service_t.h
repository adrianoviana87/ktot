#pragma once
#include <memory>
#include <optional>
#include <vector>
#include <string>
#include "ktot/domain/task_repository_t.h"

namespace ktot
{
  class task_service_t
  {
    public:
      task_service_t(std::shared_ptr<task_repository_t> repository);

      std::string save(task_t& task); 
      std::vector<task_t> list();
      std::optional<task_t> get(std::string id);
    private:
      std::shared_ptr<task_repository_t> m_repository;
  };
}

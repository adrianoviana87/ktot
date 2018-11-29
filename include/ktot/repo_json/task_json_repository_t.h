#pragma once
#include <vector>

#include "ktot/domain/task_t.h"
#include "ktot/domain/task_repository_t.h"

namespace ktot
{
  class task_json_repository_t : public task_repository_t
  {
    public:
      void save(task_t& task) override;
      std::vector<task_t> list() override;
      std::optional<task_t> get(std::string id) override;
  };
}

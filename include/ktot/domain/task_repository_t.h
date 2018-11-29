#pragma once
#include <vector>
#include <string>
#include <optional>
#include "ktot/domain/task_t.h"
namespace ktot
{
  class task_repository_t
  {
    public:
      virtual void save(task_t& task) = 0;
      virtual std::vector<task_t> list() = 0;
      virtual std::optional<task_t> get(std::string id) = 0;
      virtual ~task_repository_t() = default;
  };
}

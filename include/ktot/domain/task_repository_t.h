#pragma once
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "ktot/domain/task_t.h"
namespace ktot {
class task_repository_t {
 public:
  virtual void save(task_ptr task) = 0;
  virtual std::vector<task_ptr> list() = 0;
  virtual task_ptr get(std::string id) = 0;
  virtual ~task_repository_t() = default;
};

using task_repository_ptr = std::shared_ptr<task_repository_t>;
}  // namespace ktot

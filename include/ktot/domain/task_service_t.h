#pragma once
#include <memory>
#include <string>
#include <vector>
#include "ktot/domain/task_filter_t.h"
#include "ktot/domain/task_repository_t.h"

namespace ktot {
class task_service_t {
 public:
  task_service_t(task_repository_ptr repository);

  std::string save(task_ptr task);
  std::vector<task_ptr> list();
  task_ptr get(std::string id);

  task_ptr start(const task_filter_t &filter);
  void terminate_all();
  task_ptr find(const task_filter_t &filter);

 private:
  task_repository_ptr m_repository;
};

using task_service_ptr = std::shared_ptr<task_service_t>;
}  // namespace ktot

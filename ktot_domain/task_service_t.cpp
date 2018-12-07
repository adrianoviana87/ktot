#include "ktot/domain/task_service_t.h"

#include <algorithm>

namespace ktot {
task_service_t::task_service_t(task_repository_ptr repository)
    : m_repository(repository) {}

std::string task_service_t::save(task_ptr task) {
  m_repository->save(task);
  return task->id();
}

std::vector<task_ptr> task_service_t::list() { return m_repository->list(); }

task_ptr task_service_t::get(std::string id) { return m_repository->get(id); }

task_ptr task_service_t::start(const task_filter_t &filter) {
  auto found_task = find(filter);
  if (!found_task && !filter.name.empty()) {
    found_task = std::make_shared<task_t>(filter.name);
    found_task->external_id(filter.external_id);
  }

  if (found_task) {
    terminate_all();
    found_task->start();
    save(found_task);
  }

  return found_task;
}

void task_service_t::terminate_all() {
  auto tasks = list();
  for (auto &task : tasks) {
    if (task->terminate()) {
      save(task);
    }
  }
}

task_ptr task_service_t::find(const task_filter_t &filter) {
  auto tasks = list();
  auto task_iterator =
      std::find_if(std::begin(tasks), std::end(tasks), [&](auto &t) {
        if (filter.current) {
          return t->is_incomplete();
        }

        return (filter.name.empty() || t->name() == filter.name) &&
               (filter.external_id.empty() ||
                t->external_id() == filter.external_id);
      });

  if (task_iterator == std::end(tasks)) {
    return nullptr;
  }

  return *task_iterator;
}

}  // namespace ktot

#pragma once
#include <memory>
#include <ostream>
#include "ktot/crosscutting/app_settings_t.h"
#include "ktot/domain/task_filter_t.h"
#include "ktot/domain/task_service_t.h"

namespace ktot {
void print_task_title(const task_t& task, std::ostream& output);
void print_task_duration(const work_t& work, std::ostream& output);

class ktot_app_t {
 public:
  ktot_app_t(std::ostream& output, app_settings_ptr settings,
             task_service_ptr task_service);

  void list_tasks(const task_filter_t& filter);
  void list_tasks();
  void save_settings();
  void init();
  void start_task(const task_filter_t& filter);
  void edit_task_ended_at(const task_filter_t& filter,
                          const std::string& ended_at_str);
  void edit_tasks_path(const std::string& tasks_path);
  void end_all_tasks();
  task_ptr find_task(const task_filter_t& filter);
  void print(const task_t& task);
  void print_current_task();
  app_settings_ptr settings() const;

 private:
  void ensure_settings_paths();
  const char* m_date_format = "%Y-%m-%d %H:%M:%S";
  task_service_ptr m_task_service;

  app_settings_ptr m_settings;
  std::ostream& m_output;
};

using ktot_app_ptr = std::shared_ptr<ktot_app_t>;
}  // namespace ktot

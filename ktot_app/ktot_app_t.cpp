#include "ktot_app_t.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <optional>
#include <ratio>
#include <thread>
#include "ktot/crosscutting/format_time_t.h"
#include "ktot/crosscutting/hour_fraction_t.h"
#include "ktot/crosscutting/serialization.h"
#include "ktot/crosscutting/time_utils.h"
#include "ktot/crosscutting/tui_utils.h"

using namespace std::chrono_literals;
namespace ktot {
void print_task_title(const task_t& task, std::ostream& output) {
  output << "Task";
  if (!task.external_id().empty()) {
    output << " (" << task.external_id() << ")";
  }

  output << "      : " << task.name() << std::endl;
}

void print_task_duration(const work_t& work, std::ostream& output) {
  auto now = std::chrono::system_clock::now();
  work.duration();
  output << "WORKING FOR " << hour_fraction_t{work.duration()}
         << " (fractions of an hour)" << std::endl;
}

ktot_app_t::ktot_app_t(std::ostream& output, app_settings_ptr settings,
                       task_service_ptr task_service)
    : m_output(output),
      m_settings(settings),
      m_task_service(std::move(task_service)) {}

void ktot_app_t::init() { ensure_settings_paths(); }

void ktot_app_t::edit_tasks_path(const std::string& tasks_path) {
  m_settings->tasks_path = tasks_path;
  ensure_settings_paths();
  save_settings();
}

void ktot_app_t::ensure_settings_paths() {
  std::filesystem::create_directories(m_settings->tasks_path);
}

void ktot_app_t::save_settings() { serialize(*m_settings); }

void ktot_app_t::list_tasks() {
  auto tasks = m_task_service->list();
  for (auto& task : tasks) {
    print(*task);
  }
}

void ktot_app_t::list_tasks(const task_filter_t& filter) {
  auto found_task = m_task_service->find(filter);
  if (found_task) {
    print(*found_task);
  } else {
    m_output << "Task not found." << std::endl;
  }
}

void ktot_app_t::edit_task_ended_at(const task_filter_t& filter,
                                    const std::string& ended_at_str) {
  auto task = m_task_service->find(filter);
  if (!task) {
    m_output << "Task not found." << std::endl;
    return;
  }

  auto ended_at =
      make_time<work_t::time_point::clock>(ended_at_str, m_date_format);
  if (!ended_at) {
    m_output << "Wrong time format. Try \"yyyy/mm/dd hh:MM:ss\" -> "
             << format_time_t{work_t::time_point::clock::now(), m_date_format}
             << std::endl;
    return;
  }

  auto works = task->incomplete_works();
  if (works.empty()) {
    works = task->works();
  }

  if (works.empty()) {
    m_output << "No works found to edit." << std::endl;
    return;
  }

  auto work = *(std::end(works) - 1);
  if (ended_at < work->startedAt()) {
    m_output << "end time (" << format_time_t{*ended_at, m_date_format}
             << ") must be greater or equal than start time." << std::endl;
    return;
  }

  work->endedAt(ended_at);
  m_task_service->save(task);
  print(*task);
}

void ktot_app_t::print(const task_t& task) {
  print_task_title(task, m_output);
  m_output << "Total     : " << hour_fraction_t{task.total_works()}
           << std::endl;
  m_output << "Today     : " << hour_fraction_t{task.total_works_today()}
           << std::endl;
  auto works = task.works();
  m_output << "Works     : " << task.works().size() << std::endl;
  for (auto& work : works) {
    m_output << "Started at: "
             << format_time_t{work->startedAt(), m_date_format} << std::endl;
    if (!work->endedAt()) {
      print_task_duration(*work, m_output);
    } else {
      m_output << "Ended at  : "
               << format_time_t{*work->endedAt(), m_date_format} << std::endl;
      m_output << "Duration  : "
               << hour_fraction_t{(*work->endedAt()) - work->startedAt()}
               << " (fractions of an hour)" << std::endl;
    }

    m_output << "....." << std::endl;
  }

  m_output << "================================" << std::endl;
}

void ktot_app_t::start_task(const task_filter_t& filter) {
  task_ptr task{};
  if (filter.current || !filter.external_id.empty() || !filter.name.empty()) {
    task = m_task_service->start(filter);
  }

  if (task) {
    print(*task);
  } else {
    m_output << "No task found to start." << std::endl;
  }
}

app_settings_ptr ktot_app_t::settings() const { return m_settings; }

void ktot_app_t::end_all_tasks() {
  auto terminated = m_task_service->terminate_all();
  if (terminated.empty()) {
    m_output << "There are no running tasks." << std::endl;
    return;
  }

  m_output << "Stoped tasks:" << std::endl;
  for (auto& task : terminated) {
    print(*task);
  }
}

void ktot_app_t::print_current_task() {
  auto tasks = m_task_service->list();
  auto cur_task = std::find_if(std::begin(tasks), std::end(tasks),
                               [](auto& t) { return t->is_incomplete(); });

  if (cur_task != std::end(tasks)) {
    print_task_title(**cur_task, m_output);
    auto works = (*cur_task)->works();
    auto cur_work = std::find_if(std::begin(works), std::end(works),
                                 [](auto& w) { return !w->endedAt(); });

    if (cur_work != std::end(works)) {
      while (true) {
        print_task_duration(**cur_work, m_output);
        std::this_thread::sleep_for(1s);
        tui::clear_last_line();
      }
    }
  }
}

}  // namespace ktot
#include "console_app_t.h"
#include <iostream>
#include <string>
#include "ktot/crosscutting/serialization.h"

namespace ktot {

console_app_t::console_app_t(ktot_app_ptr app)
    : m_app(app),
      m_args_parser(
          {{{"help", {"-h", "--help"}, "shows this help message", 0},
            {"list", {"-l", "--list"}, "list tasks (may be filtered)", 0},
            {"start", {"-s", "--start"}, "starts a task by name", 0},
            {"stop", {"-S", "--stop"}, "stops all tasks", 0},
            {"edit", {"--edit"}, "edit mode", 0},
            {"current", {"-c", "--current"}, "selects the current task", 0},
            {"ended at", {"--ended-at"}, "sets when the work has stoped", 1},
            {"name", {"-n", "--task-name"}, "sets the name of the task", 1},
            {"tasks path",
             {"--tasks-path"},
             "sets the directory on which the tasks are saved",
             1},
            {"external id",
             {"-i", "--task-id"},
             "set the id of the task",
             1}}}),
      m_args() {}

int console_app_t::run(int argc, char* argv[]) {
  try {
    m_args = m_args_parser.parse(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  if (m_args["help"]) {
    argagg::fmt_ostream fmt(std::cerr);
    fmt << m_args_parser;
  } else {
    init_task_filter();
    if (m_args["list"]) {
      list();
    } else if (m_args["edit"]) {
      edit();
    } else if (m_args["start"]) {
      start();
    } else if (m_args["stop"]) {
      stop();
    } else if (m_args["edit"]) {
      edit();
    }
  }

  return 0;
}

void console_app_t::init_task_filter() {
  m_task_filter.current = m_args["current"];
  if (m_args["name"]) {
    m_task_filter.name = m_args["name"].as<std::string>();
  }

  if (m_args["external id"]) {
    m_task_filter.external_id = m_args["external id"].as<std::string>();
  }
}

void console_app_t::list() { m_app->list_tasks(m_task_filter); }

void console_app_t::edit() {
  auto something_to_edit = false;
  if (m_args["tasks path"]) {
    something_to_edit = true;
    m_app->edit_tasks_path(m_args["tasks path"].as<std::string>());
  }

  if (m_args["ended at"]) {
    something_to_edit = true;
    m_app->edit_task_ended_at(m_task_filter,
                              m_args["ended at"].as<std::string>());
    return;
  }

  if (!something_to_edit) {
    std::cerr << "edit what?" << std::endl;
  }
}

void console_app_t::start() { m_app->start_task(m_task_filter); }

void console_app_t::stop() { m_app->end_all_tasks(); }

}  // namespace ktot
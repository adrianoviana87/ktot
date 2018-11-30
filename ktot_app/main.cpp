#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "ktot/domain/task_t.h"
#include "ktot/domain/task_service_t.h"
#include "ktot/repo_json/task_json_repository_t.h"
#include "ktot/crosscutting/serialization.h"

#include <chrono>
#include <ratio>
#include <ctime>
#include <iomanip>

#include "argagg.hpp"

#include "ktot_app_t.h"

int command_line_mode(ktot::ktot_app_t &app, int argc, char *argv[])
{
  argagg::parser arg_parser = {{{"help",
                                 {"-h", "--help"},
                                 "shows this help message",
                                 0},
                                {"set task dir",
                                 {"--set-task-dir"},
                                 "sets the directory on which the tasks are saved",
                                 1},
                                {"set project dir",
                                 {"--set-proj-dir"},
                                 "sets the directory on which the projects are saved",
                                 1},
                                {"list",
                                 {"--list"},
                                 "list all tasks",
                                 0},
                                {"current",
                                 {"--current"},
                                 "prints the current working task",
                                 0},
                                {"start",
                                 {"--start"},
                                 "starts a task by name",
                                 1},
                                {"stop",
                                 {"--stop"},
                                 "stops all tasks",
                                 0}}};

  argagg::parser_results args_result;

  try
  {
    args_result = arg_parser.parse(argc, argv);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  if (args_result["help"])
  {
    argagg::fmt_ostream fmt(std::cerr);
    fmt << arg_parser;
    return 0;
  }

  if (args_result["set task dir"])
  {
    app.settings()->tasks_path = args_result["set task dir"].as<std::string>();
    ktot::serialize(*app.settings());
    app.init();
  }

  if (args_result["list"])
  {
    app.list_tasks();
  }

  if (args_result["start"])
  {
    app.start_task_by_name(args_result["start"].as<std::string>());
  }

  if (args_result["stop"])
  {
    app.end_all_tasks();
  }

  if (args_result["current"])
  {
    app.print_current_task();
  }

  return 0;
}

int main(int argc, char *argv[])
{
  auto settings = std::make_shared<ktot::app_settings_t>();
  ktot::deserialize(*settings);

  ktot::ktot_app_t app{
      std::cout,
      settings,
      std::make_shared<ktot::task_service_t>(
          std::make_shared<ktot::task_json_repository_t>(settings))};

  app.init();

  if (argc > 1)
  {
    return command_line_mode(app, argc, argv);
  }

  app.list_tasks();
  std::cout << "TODO: Interactive mode" << std::endl;
  return 0;
}

#include <iostream>
#include "ktot/crosscutting/serialization.h"
#include "ktot/domain/task_service_t.h"
#include "ktot/domain/task_t.h"
#include "ktot/repo_json/task_json_repository_t.h"

#include "console_app_t.h"
#include "ktot_app_t.h"

int main(int argc, char *argv[]) {
  auto settings = std::make_shared<ktot::app_settings_t>();
  ktot::deserialize(*settings);

  auto app = std::make_shared<ktot::ktot_app_t>(
      std::cout, settings,
      std::make_shared<ktot::task_service_t>(
          std::make_shared<ktot::task_json_repository_t>(settings)));

  app->init();

  if (argc > 1) {
    ktot::console_app_t console_app{app};
    return console_app.run(argc, argv);
  }

  app->list_tasks();
  app->print_current_task();
  return 0;
}

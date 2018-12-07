#include "ktot/crosscutting/serialization.h"
#include <fstream>
#include <iomanip>
#include "json.hpp"

using json = nlohmann::json;

namespace ktot {
std::string expand_user(std::string path) {
  if (!path.empty() && path[0] == '~') {
    assert(path.size() == 1 or path[1] == '/');
    char const *home = getenv("HOME");
    if (home || ((home = getenv("USERPROFILE")))) {
      path.replace(0, 1, home);
    } else {
      char const *hdrive = getenv("HOMEDRIVE"), *hpath = getenv("HOMEPATH");
      assert(hdrive);
      assert(hpath);
      path.replace(0, 1, std::string(hdrive) + hpath);
    }
  }

  return path;
}

std::string get_settings_file_path() {
  constexpr auto settings_file_path = "~/.ktot.json";
  return expand_user(settings_file_path);
}

void serialize(const app_settings_t &settings) {
  json j;
  j["projects_path"] = settings.projects_path;
  j["tasks_path"] = settings.tasks_path;

  std::ofstream output_file(get_settings_file_path());

  output_file << std::setw(4) << j;
}

void deserialize(app_settings_t &settings) {
  std::ifstream input_file(get_settings_file_path());
  if (input_file) {
    json j;
    input_file >> j;
    settings.tasks_path = expand_user(j["tasks_path"].get<std::string>());
    settings.projects_path = expand_user(j["projects_path"].get<std::string>());
  } else {
    settings.tasks_path = expand_user("~/ktot-tasks");
    settings.projects_path = expand_user("~/ktot-projects");
  }
}
}  // namespace ktot
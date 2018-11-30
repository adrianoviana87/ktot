#include "ktot/repo_json/task_json_repository_t.h"
#include "json.hpp"
#include <iostream>
#include <optional>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include "sole.hpp"

using json = nlohmann::json;
using time_rep = ktot::work_t::time_point::rep;
using time_point = ktot::work_t::time_point;
using duration = ktot::work_t::time_point::duration;

namespace fs = std::filesystem;

std::string generate_uuid()
{
  sole::uuid u1 = sole::uuid1();
  return u1.str();
}

time_point toTimePoint(time_rep val)
{
  duration secs{val};
  time_point t{secs};
  return t;
}

void serialize(json& j, ktot::work_t work)
{
  j["startedAt"] = work.startedAt().time_since_epoch().count();
  if (work.endedAt())
  {
    j["endedAt"] = work.endedAt()->time_since_epoch().count();
  }
  else
  {
    j["endedAt"] = nullptr;
  }
}

void deserialize(json&j, ktot::work_t& work)
{
  work.startedAt(toTimePoint(j["startedAt"].get<time_rep>()));
  if (!j["endedAt"].is_null())
  {
    auto endedAt = j["endedAt"].get<time_rep>();
    work.endedAt(toTimePoint(endedAt));
  }
}

void deserialize(json& j, ktot::task_t& task)
{
  task.id(j["id"].get<std::string>());
  task.externalId(j["externalId"].get<std::string>());
  task.name(j["name"].get<std::string>());
  auto jArray = j["works"];
  std::vector<ktot::work_ptr> works{};
  for(auto jItem : jArray)
  {
    auto work = std::make_shared<ktot::work_t>();
    deserialize(jItem, *work);
    works.push_back(work);
  }

  task.works(works);
}

void serialize(json& j, ktot::task_t& task)
{
  j["id"] = task.id();
  j["name"] = task.name();
  j["externalId"] = task.externalId();

  auto jArray = json::array();
  for(auto& work : task.works())
  {
    auto jItem = json::object();
    serialize(jItem, *work);
    jArray.push_back(jItem);
  }

  j["works"] = jArray;
}

namespace ktot
{
  task_json_repository_t::task_json_repository_t(
    app_settings_ptr settings
  ) : m_settings(settings)
  {}

  void task_json_repository_t::save(task_ptr task)
  {
    if (task->id().empty())
    {
      task->id(generate_uuid());
    }

    json j;
    serialize(j, *task);
    std::ofstream f(m_settings->tasks_path + task->id() + ".json");
    f << std::setw(4) << j << std::endl;
  }

  std::vector<task_ptr> task_json_repository_t::list()
  {
    std::vector<task_ptr> tasks{};
    for (auto path: fs::directory_iterator(m_settings->tasks_path))
    {
      if (path.is_regular_file())
      {
        auto p = path.path();
        auto task = get_by_path(p);
        if (task)
        {
          tasks.push_back(task);
        }
      }
    }

    return tasks;
  }

  task_ptr task_json_repository_t::get_by_path(fs::path path)
  {
    if (path.has_filename() && path.has_extension())
    {
      std::ifstream inputFile(path);
      if (inputFile)
      {
        json j;
        inputFile >> j;
        auto task = std::make_shared<task_t>();
        deserialize(j, *task);
        return task;
      }
    }

    return nullptr;
  }

  task_ptr task_json_repository_t::get(std::string id)
  {
    fs::path path = m_settings->tasks_path + id + ".json";
    return get_by_path(path);
  }

}

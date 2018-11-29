#include "ktot/repo_json/task_json_repository_t.h"
#include "json.hpp"
#include <iostream>
#include <optional>
#include <iomanip>
#include <fstream>
#include "sole.hpp"

using json = nlohmann::json;
using time_rep = ktot::work_t::time_point::rep;
using time_point = ktot::work_t::time_point;
using duration = ktot::work_t::time_point::duration;

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

void serialize(json& j, ktot::work_t& work)
{
  j["startedAt"] = work.startedAt().time_since_epoch().count();
  j["endedAt"] = work.endedAt().time_since_epoch().count();
}

void deserialize(json&j, ktot::work_t& work)
{
  work.startedAt(toTimePoint(j["startedAt"].get<time_rep>()));
  
  if(!j["endedAt"].empty())
  {
    work.endedAt(toTimePoint(j["endedAt"].get<time_rep>()));
  }
}

void deserialize(json& j, ktot::task_t& task)
{
  task.id(j["id"].get<std::string>());
  task.externalId(j["externalId"].get<std::string>());
  task.name(j["name"].get<std::string>());
  auto jArray = j["works"];
  std::vector<ktot::work_t> works{};
  for(auto jItem : jArray)
  {
    ktot::work_t work{};
    deserialize(jItem, work);
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
  for(auto work : task.works())
  {
    auto jItem = json::object();
    serialize(jItem, work);
    jArray.push_back(jItem);
  }

  j["works"] = jArray;
}

namespace ktot
{
  void task_json_repository_t::save(task_t& task)
  {
    if (task.id().empty())
    {
      task.id(generate_uuid());
    }

    json j;
    serialize(j, task);
    std::ofstream f(task.id() + ".json");
    f << std::setw(4) << j << std::endl;
  }

  std::vector<task_t> task_json_repository_t::list()
  {
    return {
      { "Task 1" },
      { "Task 2" }
    };
  }

  std::optional<task_t> task_json_repository_t::get(std::string id)
  {
    std::ifstream inputFile(id + ".json");
    if (inputFile)
    {
      json j;
      inputFile >> j;
      task_t task = {};
      deserialize(j, task);
      return task;
    }

    return std::optional<task_t>(std::nullopt);
  }

}

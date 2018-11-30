#include "ktot/domain/task_t.h"
#include <string>
#include <chrono>
#include <algorithm>

namespace ktot
{
task_t::task_t(std::string name) : m_name(name)
{
}

const std::string &task_t::name() const
{
  return m_name;
}

void task_t::name(std::string val)
{
  m_name = val;
}

const std::string &task_t::externalId() const
{
  return m_externalId;
}

void task_t::externalId(std::string val)
{
  m_externalId = val;
}

const std::string &task_t::id() const
{
  return m_id;
}

void task_t::id(std::string val)
{
  m_id = val;
}

const std::vector<work_ptr> &ktot::task_t::works() const
{
  return m_works;
}

void task_t::works(std::vector<ktot::work_ptr> val)
{
  m_works = val;
}

bool task_t::finish_incomplete()
{
  auto any_incomplete = is_incomplete();
  if (any_incomplete)
  {
    for (auto &work : incomplete_works())
    {
      work->endedAt(work->startedAt());
    }
  }

  return any_incomplete;
}

work_ptr task_t::start()
{
  finish_incomplete();
  auto work = std::make_shared<work_t>(std::chrono::system_clock::now());
  m_works.push_back(work);
  return work;
}

bool task_t::is_incomplete() const
{
  return incomplete_works().size() > 0;
}

std::vector<work_ptr> task_t::incomplete_works() const
{
  std::vector<work_ptr> works{};
  for (auto &work : m_works)
  {
    if (!work->endedAt())
    {
      works.push_back(work);
    }
  }

  return works;
}
} // namespace ktot
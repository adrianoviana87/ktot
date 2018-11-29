#include "ktot/domain/task_t.h"
#include <string>

ktot::task_t::task_t(std::string name): m_name(name)
{
}

const std::string& ktot::task_t::name() const
{
  return m_name;
}

void ktot::task_t::name(std::string val)
{
  m_name = val;
}

const std::string& ktot::task_t::externalId() const
{
  return m_externalId;
}

void ktot::task_t::externalId(std::string val)
{
  m_externalId = val;
}

const std::string& ktot::task_t::id() const
{
  return m_id;
}

void ktot::task_t::id(std::string val)
{
  m_id = val;
}

const std::vector<ktot::work_t>& ktot::task_t::works() const
{
  return m_works;
}

void ktot::task_t::works(std::vector<ktot::work_t> val)
{
  m_works = val;
}

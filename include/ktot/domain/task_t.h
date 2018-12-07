#pragma once

#include "ktot/domain/work_t.h"

#include <memory>
#include <string>
#include <vector>

namespace ktot {
class task_t {
 public:
  const std::string &name() const;
  void name(std::string val);

  const std::string &external_id() const;
  void external_id(std::string val);

  const std::string &id() const;
  void id(std::string val);

  const std::vector<work_ptr> &works() const;
  void works(std::vector<work_ptr> val);

  work_ptr start();

  task_t(std::string name);
  task_t() = default;
  bool finish_incomplete();
  bool terminate();
  bool is_incomplete() const;
  std::chrono::seconds total_works() const;
  std::chrono::seconds total_works_in_date(work_t::time_point time_point) const;
  std::chrono::seconds total_works_today() const;
  std::vector<work_ptr> incomplete_works() const;
 private:
  std::string m_name;
  std::string m_externalId;
  std::string m_id;
  std::vector<work_ptr> m_works;
};

using task_ptr = std::shared_ptr<task_t>;
}  // namespace ktot

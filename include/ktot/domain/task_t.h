#pragma once

#include "ktot/domain/work_t.h"

#include <string>
#include <vector>
#include <memory>

namespace ktot {
  class task_t {
  public:
    const std::string& name() const;
    void name(std::string val);

    const std::string& externalId() const;
    void externalId(std::string val);

    const std::string& id() const;
    void id(std::string val);

    const std::vector<work_ptr>& works() const;
    void works(std::vector<work_ptr> val);

    work_ptr start();

    task_t(std::string name);
    task_t() = default;
    bool finish_incomplete();
    bool is_incomplete() const;
  private:
    std::vector<work_ptr> incomplete_works() const;
    std::string m_name;
    std::string m_externalId;
    std::string m_id;
    std::vector<work_ptr> m_works;
  };

  using task_ptr = std::shared_ptr<task_t>;
}

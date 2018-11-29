#pragma once

#include "ktot/domain/work_t.h"

#include <string>
#include <vector>

namespace ktot {
  class task_t {
  public:
    const std::string& name() const;
    void name(std::string val);

    const std::string& externalId() const;
    void externalId(std::string val);

    const std::string& id() const;
    void id(std::string val);

    const std::vector<work_t>& works() const;
    void works(std::vector<work_t> val);

    task_t(std::string name);
    task_t() = default;
  private:
    std::string m_name;
    std::string m_externalId;
    std::string m_id;
    std::vector<work_t> m_works;
  };
}

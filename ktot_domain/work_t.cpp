#include "ktot/domain/work_t.h"
#include <chrono>

namespace ktot {
work_t::work_t(work_t::time_point startedAt) : m_startedAt(startedAt) {}

work_t::work_t(work_t::time_point startedAt, work_t::time_point endedAt)
    : m_startedAt(startedAt), m_endedAt(endedAt) {}

work_t::time_point work_t::startedAt() const { return m_startedAt; }

void work_t::startedAt(work_t::time_point val) { m_startedAt = val; }

std::optional<work_t::time_point> work_t::endedAt() const { return m_endedAt; }

void work_t::endedAt(std::optional<work_t::time_point> val) { m_endedAt = val; }

std::chrono::seconds work_t::duration() const {
  auto end = m_endedAt ? *m_endedAt : std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::seconds>(end - m_startedAt);
}
}  // namespace ktot

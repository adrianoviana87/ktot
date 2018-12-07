#pragma once

#include <chrono>
#include <memory>
#include <optional>

namespace ktot {
class work_t {
 public:
  using time_point = std::chrono::system_clock::time_point;
  work_t() = default;
  work_t(time_point startedAt);
  work_t(time_point startedAt, time_point endedAt);

  time_point startedAt() const;
  void startedAt(time_point val);

  std::optional<time_point> endedAt() const;
  void endedAt(std::optional<time_point> val);

  std::chrono::seconds duration() const;

 private:
  time_point m_startedAt;
  std::optional<time_point> m_endedAt;
};

using work_ptr = std::shared_ptr<work_t>;
}  // namespace ktot

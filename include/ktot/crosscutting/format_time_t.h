#pragma once
#include <chrono>
#include <ctime>
#include <iomanip>
#include <ostream>
#include <ratio>
#include <string>

namespace ktot {
template <typename Clock, typename Duration>
class format_time_t {
 public:
  using time_point_t = std::chrono::time_point<Clock, Duration>;

  format_time_t(const time_point_t &time_point, const std::string &format)
      : m_time_point(time_point), m_format(format) {}

  template <typename C, typename D>
  friend std::ostream &operator<<(std::ostream &stream,
                                  const format_time_t<C, D> &format_time);
  const time_point_t &time_point() const { return m_time_point; }
  const std::string &format() const { return m_format; }

 private:
  time_point_t m_time_point;
  std::string m_format;
};

template <typename C, typename D>
std::ostream &operator<<(std::ostream &stream,
                         const format_time_t<C, D> &format_time) {
  const time_t time = C::to_time_t(format_time.time_point());
  struct tm *timeinfo;
  timeinfo = localtime(&time);
  char buffer[80];
  strftime(buffer, 80, format_time.format().c_str(), timeinfo);
  return stream << buffer;
}
}  // namespace ktot

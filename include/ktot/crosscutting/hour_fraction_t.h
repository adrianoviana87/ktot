#pragma once
#include <chrono>
#include <ostream>

namespace ktot {
template <typename Rep, typename Period>
class hour_fraction_t {
 public:
  using Duration = std::chrono::duration<Rep, Period>;
  hour_fraction_t(const Duration &duration) : m_duration(duration) {
    auto duration_secs =
        std::chrono::duration_cast<std::chrono::seconds>(duration);
    auto seconds_of_hour = (60.0 * 60.0);
    m_fraction = duration_secs.count() / seconds_of_hour;
  }

  template <typename R, typename P>
  friend std::ostream &operator<<(std::ostream &stream,
                                  const hour_fraction_t<R, P> &hour_fraction);

 private:
  Duration m_duration;
  double m_fraction;
};

template <typename R, typename P>
std::ostream &operator<<(std::ostream &stream,
                         const hour_fraction_t<R, P> &hour_fraction) {
  return stream << hour_fraction.m_fraction;
}
}  // namespace ktot

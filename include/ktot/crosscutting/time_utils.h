#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <optional>

namespace ktot {
template <typename t_clock, typename t_duration>
bool is_in_date(std::chrono::time_point<t_clock, t_duration> day,
                std::chrono::time_point<t_clock, t_duration> time_point) {
  time_t day_tt = t_clock::to_time_t(day);
  time_t time_point_tt = t_clock::to_time_t(time_point);
  tm day_tm = *localtime(&day_tt);
  tm time_point_tm = *localtime(&time_point_tt);

  return day_tm.tm_year == time_point_tm.tm_year &&
         day_tm.tm_mon == time_point_tm.tm_mon &&
         day_tm.tm_mday == time_point_tm.tm_mday;

  return false;
}

template <typename t_clock, typename t_duration>
bool is_in_today(std::chrono::time_point<t_clock, t_duration> time_point) {
  return is_in_date(std::chrono::system_clock::now(), time_point);
}
template <typename t_clock>
std::optional<std::chrono::time_point<t_clock, typename t_clock::duration>>
make_time(const std::string& str, const std::string& format) {
  if (str.empty()) {
    return std::nullopt;
  }

  std::tm t = {};
  std::stringstream ss(str);
  ss >> std::get_time(&t, format.c_str());

  t.tm_hour -= 1;
  std::time_t tt = std::mktime(&t);

  return t_clock::from_time_t(tt);
}
}  // namespace ktot
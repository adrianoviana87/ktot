#pragma once
#include <string>

namespace ktot {
class task_filter_t {
 public:
  std::string name;
  std::string external_id;
  bool current;
};
}  // namespace ktot

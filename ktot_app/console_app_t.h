#pragma once
#include "argagg.hpp"
#include "ktot/domain/task_filter_t.h"
#include "ktot_app_t.h"

namespace ktot {

class console_app_t {
 public:
  console_app_t(ktot_app_ptr app);
  int run(int argc, char* argv[]);

 private:
  void init_task_filter();
  void start();
  void stop();
  void edit();
  void list();
  task_filter_t m_task_filter;
  argagg::parser_results m_args;
  argagg::parser m_args_parser;
  ktot_app_ptr m_app;
};

}  // namespace ktot
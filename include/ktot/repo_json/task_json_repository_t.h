#pragma once
#include <vector>
#include <memory>
#include "ktot/domain/task_t.h"
#include "ktot/domain/task_repository_t.h"
#include "ktot/crosscutting/app_settings_t.h"
#include <filesystem>

namespace ktot
{
  class task_json_repository_t : public task_repository_t
  {
    public:
      task_json_repository_t(
        app_settings_ptr settings
      );
      void save(task_ptr task) override;
      std::vector<task_ptr> list() override;
      task_ptr get(std::string id) override;
    private:
      task_ptr get_by_path(std::filesystem::path path);
      app_settings_ptr m_settings;
  };
}

#pragma once

#include <string>
#include <memory>

namespace ktot
{
    struct app_settings_t
    {
    public:
        std::string projects_path;
        std::string tasks_path;
    };

    using app_settings_ptr = std::shared_ptr<app_settings_t>;
}
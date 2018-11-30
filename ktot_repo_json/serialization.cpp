#include <fstream>
#include <iomanip>
#include "ktot/crosscutting/serialization.h"
#include "json.hpp"

using json = nlohmann::json;

namespace ktot
{
    constexpr auto settings_file_path = "~/.ktot.json";
    void serialize(const app_settings_t& settings)
    {
        json j;
        j["projects_path"] = settings.projects_path;
        j["tasks_path"] = settings.tasks_path;

        std::ofstream output_file(settings_file_path);

        output_file << std::setw(4) << j;
    }

    app_settings_t deserialize()
    {
        std::ifstream input_file(settings_file_path);
        if (input_file)
        {
            json j;
            input_file >> j;
            return
            {
                j["projects_path"].get<std::string>(),
                j["tasks_path"].get<std::string>()
            };
        }

        return
        {
            "./ktot-projects",
            "./ktot-tasks"
        };
    }
}
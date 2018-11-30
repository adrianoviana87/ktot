#include <fstream>
#include <iomanip>
#include "ktot/crosscutting/serialization.h"
#include "json.hpp"

using json = nlohmann::json;

namespace ktot
{
    constexpr auto settings_file_path = "/home/adriano/.ktot.json";
    void serialize(const app_settings_t& settings)
    {
        json j;
        j["projects_path"] = settings.projects_path;
        j["tasks_path"] = settings.tasks_path;

        std::ofstream output_file(settings_file_path);

        output_file << std::setw(4) << j;
    }

    void deserialize(app_settings_t& settings)
    {
        std::ifstream input_file(settings_file_path);
        if (input_file)
        {
            json j;
            input_file >> j;
            settings.tasks_path = j["tasks_path"].get<std::string>();
            settings.projects_path = j["projects_path"].get<std::string>();
        }
        else
        {
            settings.tasks_path = "./ktot-tasks";
            settings.projects_path = "./ktot-projects";
        }
    }
}
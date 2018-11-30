#pragma once

#include "ktot/crosscutting/app_settings_t.h"

namespace ktot
{
    void serialize(const app_settings_t& settings);
    app_settings_t deserialize();
}
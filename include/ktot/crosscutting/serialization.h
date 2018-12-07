#pragma once

#include "ktot/crosscutting/app_settings_t.h"

namespace ktot {
void serialize(const app_settings_t &settings);
void deserialize(app_settings_t &settings);
}  // namespace ktot
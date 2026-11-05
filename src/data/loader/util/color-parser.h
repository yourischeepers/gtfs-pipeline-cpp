#pragma once
#include <string>

#include "domain/util/color.h"

namespace gtfs {

    Color parse_hex_color(const std::string& hex);
}

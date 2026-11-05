#pragma once
#include <string>

#include "domain/util/color.h"

namespace gtfs {

    struct Route {
        long id{};
        std::string agency_id;
        std::string short_name;
        std::string long_name;
        Color color{};
        Color text_color{};
    };
}

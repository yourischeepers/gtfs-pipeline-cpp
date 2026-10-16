#pragma once

#include <string>
#include <vector>

#include "platform.h"

namespace gtfs {

    enum class WheelchairAccessibility {
        Unknown,
        Accessible,
        NotAccessible,
    };

    struct Stop {
        std::string id;
        std::string name;
        double lat{};
        double lon{};
        std::string timezone;
        WheelchairAccessibility wheelchair_accessible{WheelchairAccessibility::Unknown};
        std::vector<Platform> platforms;
    };
}

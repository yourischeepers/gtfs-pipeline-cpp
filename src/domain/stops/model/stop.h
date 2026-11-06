#pragma once

#include <string>
#include <vector>

#include "platform.h"
#include "../../util/timezone.h"
#include "domain/util/wheelchair-accessibility.h"

namespace gtfs {

    struct Stop {
        std::string id;
        std::string name;
        double lat{};
        double lon{};
        TimeZone timezone{TimeZone::Unknown};
        WheelchairAccessibility wheelchair_accessible{WheelchairAccessibility::Unknown};
        std::vector<Platform> platforms;
    };
}

#pragma once
#include <string>

#include "domain/util/bikes-allowed.h"
#include "domain/util/wheelchair-accessibility.h"

namespace gtfs {

    struct Trip {
        long id{};
        long route_id{};
        long service_id{};
        std::string realtime_trip_id;
        std::string headsign;
        std::string short_name;
        std::string long_name;
        bool direction_id{};
        long shape_id{};
        WheelchairAccessibility wheelchair_accessibility{WheelchairAccessibility::Unknown};
        BikesAllowed bikes_allowed{BikesAllowed::Unknown};
    };
}

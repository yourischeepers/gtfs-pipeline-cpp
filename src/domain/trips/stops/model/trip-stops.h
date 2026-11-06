#pragma once
#include <vector>

#include "trip-stop.h"

namespace gtfs {

    struct TripStops {
        uint32_t id{};
        std::vector<TripStop> stops;
    };
}

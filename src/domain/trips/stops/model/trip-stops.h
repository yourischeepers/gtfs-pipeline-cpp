#pragma once
#include <vector>

#include "trip-stop.h"

namespace gtfs {

    struct TripStops {
        long id{};
        std::vector<TripStop> stops;
    };
}

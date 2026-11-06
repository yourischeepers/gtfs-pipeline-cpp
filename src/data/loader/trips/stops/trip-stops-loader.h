#pragma once

#include <vector>
#include <string>

#include "domain/trips/stops/model/trip-stops.h"

namespace gtfs {

    class TripStopsLoader {

    public:
        [[nodiscard]] std::vector<TripStops> load_trip_stops(const std::string& dataset_directory, size_t trips_count) const;
    };
}

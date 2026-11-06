#pragma once

#include <vector>
#include <string>
#include "domain/trips/model/trip.h"

namespace gtfs {

    class TripLoader {

    public:
        [[nodiscard]] std::vector<Trip> load_trips(const std::string& dataset_directory) const;
    };
}

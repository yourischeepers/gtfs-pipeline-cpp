#pragma once

#include <vector>
#include <csv.hpp>

#include "domain/state/stops/stop.h"

namespace gtfs {

class StopLoader {

public:
    std::vector<Stop> loadStops();

private:
    struct RawStop {
        std::string id;
        std::string name;
        std::float_t lat;
        std::float_t lon;
        std::string parentStation;
        std::string timezone;
        bool wheelchairAccessible;
        std::string platformCode;
    };

    Stop mapNoParentToStop(const RawStop& raw_stop);
    Platform mapToPlatform(const RawStop& raw_stop);
    Platform generateDefaultPlatform(const Stop& stop);
    std::vector<RawStop> loadRawStops();
};

}

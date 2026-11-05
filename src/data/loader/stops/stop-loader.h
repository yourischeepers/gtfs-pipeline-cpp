#pragma once

#include <vector>
#include "../../../domain/stops/model/stop.h"

namespace gtfs {

    struct RawStop {
        std::string id;
        std::string name;
        double lat{};
        double lon{};
        std::string parent_station;
        std::string timezone;
        WheelchairAccessibility wheelchair_accessible{WheelchairAccessibility::Unknown};
        std::string platform_code;
    };

    class StopLoader {

    public:
        std::vector<Stop> load_stops(const std::string& dataset_directory) const;

    private:
        TimeZoneParser time_zone_parser;

        Stop map_no_parent_to_stop(const RawStop& raw_stop) const;
    };
}

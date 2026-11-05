#pragma once

#include <string>
#include <unordered_map>

namespace gtfs {

    enum class TimeZone {
        EuropeAmsterdam,
        Unknown,
    };

    class TimeZoneParser {

    public:
        TimeZoneParser();
        [[nodiscard]] TimeZone get_time_zone(const std::string& id) const;

    private:
        std::unordered_map<std::string, TimeZone> time_zones;
    };
}

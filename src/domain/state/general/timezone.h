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
        TimeZone getTimeZone(const std::string& id) const;

    private:
        std::unordered_map<std::string, TimeZone> time_zones;
    };
}

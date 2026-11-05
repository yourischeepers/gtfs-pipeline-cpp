#include "timezone.h"

namespace gtfs {

    TimeZoneParser::TimeZoneParser() {
        time_zones.emplace("Europe/Amsterdam", TimeZone::EuropeAmsterdam);
    }

    TimeZone TimeZoneParser::get_time_zone(const std::string& id) const {
        const auto time_zone_entry = time_zones.find(id);
        if (time_zone_entry == time_zones.end()) return TimeZone::Unknown;
        return time_zone_entry->second;
    }
}

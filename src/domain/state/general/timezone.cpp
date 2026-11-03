#include "timezone.h"

namespace gtfs {

    TimeZoneParser::TimeZoneParser() {
        time_zones.emplace("Europe/Amsterdam", TimeZone::EuropeAmsterdam);
    }

    TimeZone TimeZoneParser::getTimeZone(const std::string& id) const {
        const auto timeZoneEntry = time_zones.find(id);
        if (timeZoneEntry == time_zones.end()) return TimeZone::Unknown;
        return timeZoneEntry->second;
    }
}

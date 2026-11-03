#pragma once

#include <vector>

#include "domain/state/agencies/agency.h"

namespace gtfs {

    class AgencyLoader {

    public:
        std::vector<Agency> load_agencies(const std::string& dataset_directory) const;

    private:
        TimeZoneParser time_zone_parser;
    };
}

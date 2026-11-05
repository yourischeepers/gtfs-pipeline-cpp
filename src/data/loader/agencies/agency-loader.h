#pragma once

#include <vector>

#include "../../../domain/agencies/model/agency.h"

namespace gtfs {

    class AgencyLoader {

    public:
        std::vector<Agency> load_agencies(const std::string& dataset_directory) const;

    private:
        TimeZoneParser time_zone_parser;
    };
}

#pragma once
#include "data/state/state-snapshot.h"

namespace gtfs {

    class GtfsLoader {

    public:
        [[nodiscard]] StateSnapshot load(const std::string& dataset_directory) const;

    private:
        [[nodiscard]] std::vector<Stop> load_stops(const std::string& dataset_directory) const;
        [[nodiscard]] std::vector<Agency> load_agencies(const std::string& dataset_directory) const;
        [[nodiscard]] std::vector<Route> load_routes(const std::string& dataset_directory) const;
    };
}

#pragma once

#include <vector>
#include "domain/state/stops/stop.h"

namespace gtfs {

    std::vector<Stop> load_stops(const std::string& dataset_directory);
}

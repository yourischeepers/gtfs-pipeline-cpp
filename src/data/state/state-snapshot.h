#pragma once
#include <vector>

#include "domain/state/agencies/agency.h"
#include "domain/state/agencies/routes/route.h"
#include "domain/state/stops/stop.h"

namespace gtfs {

    struct StateSnapshot {
        std::vector<Stop> stops;
        std::vector<Agency> agencies;
        std::vector<Route> routes;
    };
}

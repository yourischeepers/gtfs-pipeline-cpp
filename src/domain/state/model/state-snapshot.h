#pragma once
#include <vector>

#include "../../agencies/model/agency.h"
#include "../../agencies/routes/model/route.h"
#include "../../stops/model/stop.h"

namespace gtfs {

    struct StateSnapshot {
        std::vector<Stop> stops;
        std::vector<Agency> agencies;
        std::vector<Route> routes;
    };
}

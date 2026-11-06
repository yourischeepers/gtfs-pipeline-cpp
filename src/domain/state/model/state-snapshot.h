#pragma once
#include <vector>

#include "domain/agencies/model/agency.h"
#include "domain/agencies/routes/model/route.h"
#include "domain/stops/model/stop.h"
#include "domain/trips/model/trip.h"

namespace gtfs {

    struct StateSnapshot {
        std::vector<Stop> stops;
        std::vector<Agency> agencies;
        std::vector<Route> routes;
        std::vector<Trip> trips;
    };
}

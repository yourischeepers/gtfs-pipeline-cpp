#pragma once
#include <vector>

#include "domain/agencies/model/agency.h"
#include "domain/agencies/routes/model/route.h"
#include "domain/stops/model/stop.h"
#include "domain/trips/model/trip.h"
#include "domain/trips/stops/model/trip-stops.h"

namespace gtfs {

    struct StateSnapshot {
        std::vector<Stop> stops;
        std::vector<Agency> agencies;
        std::vector<Route> routes;
        std::vector<Trip> trips;
        std::vector<TripStops> trip_stops;
    };
}

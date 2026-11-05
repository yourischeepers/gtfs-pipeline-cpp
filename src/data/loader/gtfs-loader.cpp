#include "gtfs-loader.h"

#include <iostream>

#include "agencies/agency-loader.h"
#include "agencies/routes/route-loader.h"
#include "data/state/state-snapshot.h"
#include "stops/stop-loader.h"

namespace gtfs {

    StateSnapshot GtfsLoader::load(const std::string& dataset_directory) const {
        StateSnapshot result;

        result.stops = load_stops(dataset_directory);
        result.agencies = load_agencies(dataset_directory);
        result.routes = load_routes(dataset_directory);

        return result;
    }

    std::vector<Stop> GtfsLoader::load_stops(const std::string& dataset_directory) const {
        const auto start = std::chrono::steady_clock::now();
        const StopLoader stop_loader;
        std::vector<Stop> stops = stop_loader.load_stops(dataset_directory);

        const auto end = std::chrono::steady_clock::now();
        const auto duration = std::chrono::duration<double, std::milli>(end - start);

        std::cout << "Loaded " << stops.size() << " stops in " << duration.count() << "ms" << std::endl;
        return stops;
    }

    std::vector<Agency> GtfsLoader::load_agencies(const std::string &dataset_directory) const {
        const auto start = std::chrono::steady_clock::now();
        const AgencyLoader agency_loader;
        std::vector<Agency> agencies = agency_loader.load_agencies(dataset_directory);

        const auto end = std::chrono::steady_clock::now();
        const auto duration = std::chrono::duration<double, std::milli>(end - start);

        std::cout << "Loaded " << agencies.size() << " agencies in " << duration.count() << "ms" << std::endl;
        return agencies;
    }

    std::vector<Route> GtfsLoader::load_routes(const std::string &dataset_directory) const {
        const auto start = std::chrono::steady_clock::now();
        const RouteLoader route_loader;
        std::vector<Route> routes = route_loader.load_routes(dataset_directory);

        const auto end = std::chrono::steady_clock::now();
        const auto duration = std::chrono::duration<double, std::milli>(end - start);

        std::cout << "Loaded " << routes.size() << " routes in " << duration.count() << "ms" << std::endl;
        return routes;
    }
}

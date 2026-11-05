#include <chrono>
#include <iostream>
#include <vector>

#include "data/loader/agencies/agency-loader.h"
#include "data/loader/agencies/routes/route-loader.h"
#include "data/loader/stops/stop-loader.h"
#include "domain/state/agencies/agency.h"
#include "domain/state/agencies/routes/route.h"

static std::vector<gtfs::Stop> setup_stops(const std::string& dataset_directory) {
    const auto start = std::chrono::steady_clock::now();
    gtfs::StopLoader stop_loader;
    const std::vector<gtfs::Stop> stops = stop_loader.load_stops(dataset_directory);

    const auto end = std::chrono::steady_clock::now();
    const auto duration = std::chrono::duration<double, std::milli>(end - start);

    std::cout << "Loaded " << stops.size() << " stops in " << duration.count() << "ms" << std::endl;
    return stops;
}

static std::vector<gtfs::Agency> setup_agencies(const std::string& dataset_directory) {
    const auto start = std::chrono::steady_clock::now();
    const gtfs::AgencyLoader agency_loader;
    const std::vector<gtfs::Agency> agencies = agency_loader.load_agencies(dataset_directory);

    const auto end = std::chrono::steady_clock::now();
    const auto duration = std::chrono::duration<double, std::milli>(end - start);
    std::cout << "Loaded " << agencies.size() << " agencies in " << duration.count() << "ms" << std::endl;
    return agencies;
}

static std::vector<gtfs::Route> setup_routes(const std::string& dataset_directory) {
    const auto start = std::chrono::steady_clock::now();
    const gtfs::RouteLoader route_loader;
    const std::vector<gtfs::Route> routes = route_loader.load_routes(dataset_directory);

    const auto end = std::chrono::steady_clock::now();
    const auto duration = std::chrono::duration<double, std::milli>(end - start);
    std::cout << "Loaded " << routes.size() << " routes in " << duration.count() << "ms" << std::endl;
    return routes;
}

static long get_memory_usage_kibibytes() {
    rusage usage{};

    if(0 == getrusage(RUSAGE_SELF, &usage)) {
        const long usage_bytes = usage.ru_maxrss;
        return usage_bytes / 1024;
    }

    return 0;
}

int main() {
    std::cout << "GTFS pipeline" << std::endl;

    std::string dataset_directory;
    std::cout << "Enter dataset directory path (leave empty for default): ";
    std::getline(std::cin, dataset_directory);

    if (dataset_directory.empty()) {
        dataset_directory = "../data/gtfs";
    }

    std::vector<gtfs::Stop> stops = setup_stops(dataset_directory);
    std::vector<gtfs::Agency> agencies = setup_agencies(dataset_directory);
    std::vector<gtfs::Route> routes = setup_routes(dataset_directory);

    std::cout << "Using " << get_memory_usage_kibibytes() << " KiB" << std::endl;
}

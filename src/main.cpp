#include <chrono>
#include <iostream>

#include "data/loader/gtfs-loader.h"
#include "data/routes/route-repository-impl.h"
#include "data/state/memory-state-data-store.h"
#include "domain/agencies/get-route-long-names-by-agency-id-use-case.h"
#include "domain/state/model/state-snapshot.h"

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

    const gtfs::GtfsLoader loader;
    const gtfs::MemoryStateDataStore data_store(loader.load(dataset_directory));
    const gtfs::RouteRepositoryImpl route_repository(data_store);
    const gtfs::GetRouteLongNamesByAgencyIdUseCase get_route_long_names_by_agency_id(route_repository);

    for (const auto& route_long_name : get_route_long_names_by_agency_id("GVB")) {
        std::cout << route_long_name << std::endl;
    }

    std::cout << "Using " << get_memory_usage_kibibytes() << " KiB" << std::endl;
}

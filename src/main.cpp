#include <chrono>
#include <iostream>

#include "data/dataset/dataset-repository-impl.h"
#include "data/loader/gtfs-loader.h"
#include "data/routes/route-repository-impl.h"
#include "data/state/memory-state-data-store.h"
#include "domain/agencies/get-route-long-names-by-agency-id-use-case.h"
#include "domain/dataset/get-newest-e-tag-use-case.h"
#include "domain/state/model/state-snapshot.h"
#include "network/dataset/dataset-data-source-impl.h"
#include <curl/curl.h>

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
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // std::string dataset_directory;
    // std::cout << "Enter dataset directory path (leave empty for default): ";
    // std::getline(std::cin, dataset_directory);
    //
    // if (dataset_directory.empty()) {
    //     dataset_directory = "../data/gtfs";
    // }
    //
    // const gtfs::GtfsLoader loader;
    // const gtfs::MemoryStateDataStore data_store(loader.load(dataset_directory));
    // const gtfs::RouteRepositoryImpl route_repository(data_store);
    // const gtfs::GetRouteLongNamesByAgencyIdUseCase get_route_long_names_by_agency_id(route_repository);
    //
    // // Loading route names
    // const auto start = std::chrono::steady_clock::now();
    // const auto route_long_names = get_route_long_names_by_agency_id("GVB");
    // const auto end = std::chrono::steady_clock::now();
    // const auto duration = std::chrono::duration<double, std::milli>(end - start);
    //
    // std::cout << "Found " << route_long_names.size() << " routes in " << duration.count() << "ms" << std::endl;
    //
    // for (const auto& route_long_name : route_long_names) {
    //     std::cout << route_long_name << std::endl;
    // }
    //
    // std::cout << "Using " << get_memory_usage_kibibytes() << " KiB" << std::endl;

    const gtfs::DatasetDataSourceImpl dataset_data_source;
    const gtfs::DatasetRepositoryImpl dataset_repository(dataset_data_source);
    const gtfs::GetNewestETagUseCase get_newest_e_tag_use_case(dataset_repository);

    const auto e_tag = get_newest_e_tag_use_case();
    std::cout << "Found ETag " << e_tag << std::endl;

    curl_global_cleanup();
}

#include <chrono>
#include <iostream>

#include "data/loader/gtfs-loader.h"
#include "data/state/memory-state-data-store.h"
#include "data/state/state-snapshot.h"

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
    gtfs::MemoryStateDataStore data_store(loader.load(dataset_directory));

    std::cout << "Using " << get_memory_usage_kibibytes() << " KiB" << std::endl;
}

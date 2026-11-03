#include <chrono>
#include <iostream>
#include <vector>
#include "data/loader/stops/stop-loader.h"

static void setup_stops(const std::string& dataset_directory) {
    const auto start = std::chrono::steady_clock::now();
    const std::vector<gtfs::Stop> stops = gtfs::load_stops(dataset_directory);

    const auto end = std::chrono::steady_clock::now();
    const auto duration = std::chrono::duration<double, std::milli>(end - start);

    std::cout << "Loaded " << stops.size() << " stops in " << duration.count() << "ms" << std::endl;
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

    setup_stops(dataset_directory);

    std::cout << "Using " << get_memory_usage_kibibytes() << " KiB" << std::endl;
}

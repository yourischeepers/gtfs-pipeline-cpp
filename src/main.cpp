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

int main() {
    std::cout << "GTFS pipeline" << std::endl;

    std::string dataset_directory;
    std::cout << "Enter dataset directory path (leave empty for default): ";
    std::getline(std::cin, dataset_directory);

    if (dataset_directory.empty()) {
        dataset_directory = "../data/gtfs";
    }

    setup_stops(dataset_directory);
}

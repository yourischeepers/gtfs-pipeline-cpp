#include <chrono>
#include <iostream>
#include <vector>
#include "domain/state/stops/stop.h"
#include "data/loader/stops/stop-loader.h"

int main() {
    std::cout << "GTFS pipeline\n";

    const auto start = std::chrono::steady_clock::now();
    gtfs::StopLoader stop_loader;
    const std::vector<gtfs::Stop> stops = stop_loader.load_stops();

    const auto end = std::chrono::steady_clock::now();
    const auto duration = std::chrono::duration<double, std::milli>(end - start);

    std::cout << "Loaded " << stops.size() << " stops in " << duration.count() << "ms" << std::endl;
}

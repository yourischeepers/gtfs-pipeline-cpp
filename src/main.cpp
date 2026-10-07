#include <iostream>
#include <vector>
#include <csv.hpp>

struct Stop {
    std::string stopId;
};

std::vector<Stop> load_stops() {
    std::cout << "Loading stops\n";

    std::vector<Stop> stops;
    csv::CSVReader reader("../data/gtfs/stops.txt");

    for (auto& row : reader) {
        Stop stop {
            .stopId = row["stop_id"].get<std::string>()
        };

        stops.push_back(stop);
    }

    return stops;
}

int main() {
    std::cout << "GTFS pipeline\n";
    std::vector<Stop> stops = load_stops();
    std::cout << "Loaded " << stops.size() << " stops\n";
    return 0;
}
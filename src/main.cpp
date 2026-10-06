#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream stream(input);
    std::string part;

    while (std::getline(stream, part, delimiter)) {
        parts.push_back(part);
    }

    return parts;
}

struct Stop {
    std::string stopId;
};

std::vector<Stop> load_stops() {
    std::cout << "Loading stops\n";

    std::vector<Stop> stops;
    std::string currentLine;
    std::fstream file("./data/gtfs/stops.txt");

    // Skip first line (header)
    getline(file, currentLine);

    while (getline(file, currentLine)) {
        std::vector<std::string> parts = split(currentLine, ',');

        Stop stop;
        stop.stopId = parts[0];

        stops.push_back(stop);
    }

    file.close();
    return stops;
}

int main() {
    std::cout << "GTFS pipeline\n";
    std::vector<Stop> stops = load_stops();
    std::cout << "Loaded " << stops.size() << " stops\n";
    return 0;
}
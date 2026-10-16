#include "stop-loader.h"
#include <unordered_map>
#include <csv.hpp>

namespace gtfs {

    struct RawStop {
        std::string id;
        std::string name;
        double lat{};
        double lon{};
        std::string parent_station;
        std::string timezone;
        WheelchairAccessibility wheelchair_accessible{WheelchairAccessibility::Unknown};
        std::string platform_code;
    };

    std::vector<Stop> StopLoader::loadStops() {
        std::vector<RawStop> raw_stops = loadRawStops();

        // <ParentStopId, Platforms>
        std::unordered_map<std::string, std::vector<Platform>> platforms;
        // <StopId, Stop>
        std::unordered_map<std::string, Stop> stops;

        // Organise stops and platforms with basic mapping
        for (auto& raw_stop : raw_stops) {
            if (raw_stop.parent_station.empty()) {
                stops[raw_stop.id] = mapNoParentToStop(raw_stop);
            } else {
                Platform platform = mapToPlatform(raw_stop);
                platforms[raw_stop.parent_station].push_back(platform);
            }
        }

        // Connect platforms to stops
        for (auto& [parent_id, plats] : platforms) {
            for (auto& platform : plats) {
                if (auto stop  = stops.find(parent_id); stop == stops.end()) {
                    std::cout << "Missing parent " << parent_id << " for platform " << platform.id << std::endl;
                } else {
                    stop->second.platforms.push_back(platform);
                }
            }
        }

        // Add default platform for stops without platforms
        for (auto& pair : stops) {
            if (!pair.second.platforms.empty()) continue;
            pair.second.platforms.push_back(generateDefaultPlatform(pair.second));
        }

        // Build final array
        std::vector<Stop> result;
        result.reserve(stops.size());
        for (auto &stop: stops | std::views::values) {
            result.push_back(std::move(stop));
        }

        return result;
    }

    Stop StopLoader::mapNoParentToStop(const RawStop& raw_stop) {
        Stop stop;

        stop.id = raw_stop.id;
        stop.name = raw_stop.name;
        stop.lat = raw_stop.lat;
        stop.lon = raw_stop.lon;
        stop.timezone = raw_stop.timezone;
        stop.wheelchair_accessible = raw_stop.wheelchair_accessible;

        return stop;
    }

    Platform StopLoader::mapToPlatform(const RawStop& raw_stop) {
        Platform platform;

        platform.id = raw_stop.id;
        platform.lat = raw_stop.lat;
        platform.lon = raw_stop.lon;
        platform.platform_code = raw_stop.platform_code;

        return platform;
    }

    Platform StopLoader::generateDefaultPlatform(const Stop &stop) {
        Platform platform;

        platform.id = stop.id;
        platform.lat = stop.lat;
        platform.lon = stop.lon;

        return platform;
    }

    std::vector<RawStop> StopLoader::loadRawStops() {
        std::vector<RawStop> raw_stops;

        csv::CSVReader reader("../data/gtfs/stops.txt");

        for (auto& row : reader) {
            RawStop raw_stop;

            // Always safe to get
            raw_stop.id = row[0].get<std::string>();
            raw_stop.name = row[2].get<std::string>();
            raw_stop.lat = row[3].get<double>();
            raw_stop.lon = row[4].get<double>();

            // Not always safe
            auto parent_station_field = row[6];
            auto timezone_field = row[7];
            auto wheelchair_accessible_field = row[8];
            auto platform_code_field = row[9];

            if (!parent_station_field.is_null()) {
                raw_stop.parent_station = parent_station_field.get<std::string>();
            }

            if (!timezone_field.is_null()) {
                raw_stop.timezone = timezone_field.get<std::string>();
            }

            switch (wheelchair_accessible_field.is_null() ? 0 : wheelchair_accessible_field.get<int>()) {
                case 1:
                    raw_stop.wheelchair_accessible = WheelchairAccessibility::Accessible;
                    break;
                case 2:
                    raw_stop.wheelchair_accessible = WheelchairAccessibility::NotAccessible;
                    break;
                default:
                    raw_stop.wheelchair_accessible = WheelchairAccessibility::Unknown;
            }

            if (!platform_code_field.is_null()) {
                raw_stop.platform_code = platform_code_field.get<std::string>();
            }

            raw_stops.push_back(raw_stop);
        }

        return raw_stops;
    }
}

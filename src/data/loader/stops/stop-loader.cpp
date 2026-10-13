#include "stop-loader.h"
#include <unordered_map>

namespace gtfs {

    std::vector<Stop> StopLoader::loadStops() {
        std::vector<RawStop> raw_stops = loadRawStops();

        // <ParentStopId, Platforms>
        std::unordered_map<std::string, std::vector<Platform>> platforms;
        // <StopId, Stop>
        std::unordered_map<std::string, Stop> stops;

        // Organise stops and platforms with basic mapping
        for (auto& raw_stop : raw_stops) {
            if (raw_stop.parentStation == "") {
                stops[raw_stop.id] = mapNoParentToStop(raw_stop);
            } else {
                if (!platforms.contains(raw_stop.parentStation)) {
                    platforms[raw_stop.parentStation];
                }

                Platform platform = mapToPlatform(raw_stop);
                platforms[raw_stop.parentStation].push_back(platform);
            }
        }

        // Connect platforms to stops
        for (auto& pair : platforms) {
            for (auto& platform : pair.second) {
                stops[pair.first].platforms.push_back(platform);
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
        for (auto& pair : stops) {
            result.push_back(pair.second);
        }

        return result;
    }

    Stop StopLoader::mapNoParentToStop(const RawStop& raw_stop) {
        Stop stop;
        Platform platform = mapToPlatform(raw_stop);

        stop.id = raw_stop.id;
        stop.name = raw_stop.name;
        stop.lat = raw_stop.lat;
        stop.lon = raw_stop.lon;
        stop.timezone = raw_stop.timezone;
        stop.wheelchairAccessible = raw_stop.wheelchairAccessible;
        stop.platforms.push_back(platform);

        return stop;
    }

    Platform StopLoader::mapToPlatform(const RawStop& raw_stop) {
        Platform platform;

        platform.id = raw_stop.id;
        platform.lat = raw_stop.lat;
        platform.lon = raw_stop.lon;
        platform.platformCode = raw_stop.platformCode;

        return platform;
    }

    Platform StopLoader::generateDefaultPlatform(const Stop &stop) {
        Platform platform;

        platform.id = stop.id;
        platform.lat = stop.lat;
        platform.lon = stop.lon;

        return platform;
    }

    std::vector<StopLoader::RawStop> StopLoader::loadRawStops() {
        std::vector<RawStop> raw_stops;

        csv::CSVReader reader("../data/gtfs/stops.txt");

        for (auto& row : reader) {
            RawStop raw_stop;

            // Always safe to get
            raw_stop.id = row["stop_id"].get<std::string>();
            raw_stop.name = row["stop_name"].get<std::string>();
            raw_stop.lat = row["stop_lat"].get<std::float_t>();
            raw_stop.lon = row["stop_lon"].get<std::float_t>();

            // Not always safe
            auto parent_station_field = row["parent_station"];
            auto timezone_field = row["stop_timezone"];
            auto wheelchairAccessibleField = row["wheelchair_boarding"];
            auto platformCodeField = row["platform_code"];

            if (!parent_station_field.is_null()) {
                raw_stop.parentStation = parent_station_field.get<std::string>();
            }

            if (!timezone_field.is_null()) {
                raw_stop.timezone = timezone_field.get<std::string>();
            }

            raw_stop.wheelchairAccessible = wheelchairAccessibleField.is_null() ? false : wheelchairAccessibleField.get<int>() == 1;

            if (!platformCodeField.is_null()) {
                raw_stop.platformCode = platformCodeField.get<std::string>();
            }


            raw_stops.push_back(raw_stop);
        }

        return raw_stops;
    }
}

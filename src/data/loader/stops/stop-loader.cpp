#include "stop-loader.h"
#include <csv.hpp>
#include <unordered_map>
#include <ranges>
#include <utility>
#include "data/loader/util/csv-util.h"

namespace gtfs {

    namespace {

        Platform map_to_platform(const RawStop& raw_stop) {
            Platform platform;

            platform.id = raw_stop.id;
            platform.lat = raw_stop.lat;
            platform.lon = raw_stop.lon;
            platform.platform_code = raw_stop.platform_code;

            return platform;
        }

        Platform generate_default_platform(const Stop& stop) {
            Platform platform;

            platform.id = stop.id;
            platform.lat = stop.lat;
            platform.lon = stop.lon;

            return platform;
        }

        std::vector<RawStop> load_raw_stops(const std::string& dataset_directory) {
            std::vector<RawStop> raw_stops;
            raw_stops.reserve(60000); // Estimate based on testing set

            csv::CSVReader reader = create_reader(dataset_directory + "/stops.txt");

            const int id_col = reader.index_of("stop_id");
            const int name_col = reader.index_of("stop_name");
            const int lat_col = reader.index_of("stop_lat");
            const int lon_col = reader.index_of("stop_lon");
            const int parent_id_col = reader.index_of("parent_station");
            const int timezone_col = reader.index_of("stop_timezone");
            const int wheelchair_accessible_col = reader.index_of("wheelchair_boarding");
            const int platform_code_col = reader.index_of("platform_code");

            for (auto& row : reader) {
                RawStop raw_stop;

                raw_stop.id = get_safely<std::string>(row, id_col, "");
                raw_stop.name = get_safely<std::string>(row, name_col, "");
                raw_stop.lat = get_safely<double>(row, lat_col, 0.0);
                raw_stop.lon = get_safely<double>(row, lon_col, 0.0);
                raw_stop.parent_station = get_safely<std::string>(row, parent_id_col, "");
                raw_stop.timezone = get_safely<std::string>(row, timezone_col, "");
                raw_stop.platform_code = get_safely<std::string>(row, platform_code_col, "");
                raw_stop.wheelchair_accessible = parse_wheelchair_accessibility(get_safely<int>(row, wheelchair_accessible_col, 0));

                raw_stops.push_back(std::move(raw_stop));
            }

            return raw_stops;
        }
    }

    Stop StopLoader::map_no_parent_to_stop(const RawStop& raw_stop) const {
        Stop stop;

        stop.id = raw_stop.id;
        stop.name = raw_stop.name;
        stop.lat = raw_stop.lat;
        stop.lon = raw_stop.lon;
        stop.timezone = time_zone_parser.get_time_zone(raw_stop.timezone);
        stop.wheelchair_accessible = raw_stop.wheelchair_accessible;

        return stop;
    }

    std::vector<Stop> StopLoader::load_stops(const std::string& dataset_directory) const {
        std::vector<RawStop> raw_stops = load_raw_stops(dataset_directory);

        // <ParentStopId, Platforms>
        std::unordered_map<std::string, std::vector<Platform>> platforms;
        platforms.reserve(raw_stops.size());
        // <StopId, Stop>
        std::unordered_map<std::string, Stop> stops;
        stops.reserve(raw_stops.size());

        // Organise stops and platforms with basic mapping
        for (const auto& raw_stop : raw_stops) {
            if (raw_stop.parent_station.empty()) {
                stops.emplace(raw_stop.id, map_no_parent_to_stop(raw_stop));
            } else {
                platforms[raw_stop.parent_station].push_back(map_to_platform(raw_stop));
            }
        }

        // Connect platforms to stops
        for (auto& [parent_id, plats] : platforms) {
            if (auto stop = stops.find(parent_id); stop != stops.end()) {
                for (auto& platform : plats) {
                    stop->second.platforms.push_back(std::move(platform));
                }
            }
        }

        // Build final array while simultaneously adding default platforms where necessary
        std::vector<Stop> result;
        result.reserve(stops.size());

        for (auto& stop: stops | std::views::values) {
            if (stop.platforms.empty()) {
                stop.platforms.push_back(generate_default_platform(stop));
            }

            result.push_back(std::move(stop));
        }

        return result;
    }
}

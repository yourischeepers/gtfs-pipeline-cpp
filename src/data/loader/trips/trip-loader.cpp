#include "trip-loader.h"
#include <csv.hpp>
#include <filesystem>
#include <iostream>

#include "data/loader/util/csv-util.h"
#include "data/loader/util/file-size.h"

namespace gtfs {

    namespace {

        size_t estimate_rows(const std::string &dataset_directory) {
            constexpr size_t row_size_bytes = 64;
            return get_file_size_bytes(dataset_directory + "/trips.txt") / row_size_bytes;
        }
    }

    std::vector<Trip> TripLoader::load_trips(const std::string &dataset_directory) const {
        csv::CSVReader reader(dataset_directory + "/trips.txt");

        const int route_id_col = reader.index_of("route_id");
        const int service_id_col = reader.index_of("service_id");
        const int trip_id_col = reader.index_of("trip_id");
        const int realtime_trip_id_col = reader.index_of("realtime_trip_id");
        const int trip_headsign_col = reader.index_of("trip_headsign");
        const int trip_short_name_col = reader.index_of("trip_short_name");
        const int trip_long_name_col = reader.index_of("trip_long_name");
        const int direction_id_col = reader.index_of("direction_id");
        const int shape_id_col = reader.index_of("shape_id");
        const int wheelchair_accessible_col = reader.index_of("wheelchair_accessible");
        const int bikes_allowed_col = reader.index_of("bikes_allowed");

        std::vector<Trip> trips;
        const size_t estimated_row_count = estimate_rows(dataset_directory);
        trips.reserve(estimated_row_count);
        std::cout << "Estimated " << estimated_row_count << " rows in trips.txt" << std::endl;

        for (auto& row : reader) {
            Trip trip;

            trip.id = get_safely<long>(row, trip_id_col, 0);
            trip.route_id = get_safely<long>(row, route_id_col, 0);
            trip.service_id = get_safely<long>(row, service_id_col, 0);
            trip.realtime_trip_id = get_safely<std::string>(row, realtime_trip_id_col, "");
            trip.headsign = get_safely<std::string>(row, trip_headsign_col, "");
            trip.short_name = get_safely<std::string>(row, trip_short_name_col, "");
            trip.long_name = get_safely<std::string>(row, trip_long_name_col, "");
            trip.direction_id = get_safely<int>(row, direction_id_col, 0) == 1;
            trip.shape_id = get_safely<long>(row, shape_id_col, 0);
            trip.wheelchair_accessibility = parse_wheelchair_accessibility(get_safely<int>(row, wheelchair_accessible_col, 0));
            trip.bikes_allowed = parse_bikes_allowed(get_safely<int>(row, bikes_allowed_col, 0));

            trips.push_back(std::move(trip));
        }

        return trips;
    }
}

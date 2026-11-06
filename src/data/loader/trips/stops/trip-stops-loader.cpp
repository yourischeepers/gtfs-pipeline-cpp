#include "trip-stops-loader.h"

#include <csv.hpp>

#include "data/loader/util/csv-util.h"
#include "domain/trips/stops/model/trip-stops.h"

namespace gtfs {

    namespace {

        long map_time(const std::string& input) {
            long result = 0;
            const size_t input_len = input.size();

            if (input_len == 8) result += (input[0] - '0') * 10 * 60 * 60;
            result += (input[input_len - 7] - '0') * 60 * 60;
            result += (input[input_len - 5] - '0') * 10 * 60;
            result += (input[input_len - 4] - '0') * 60;
            result += (input[input_len - 2] - '0') * 10;
            result += input[input_len - 1] - '0';

            return result;
        }

        PickUpType map_pickup_type(const int data) {
            switch (data) {
                case 1:
                    return PickUpType::Unavailable;
                case 2:
                    return PickUpType::CallAgency;
                case 3:
                    return PickUpType::ContactDriver;
                default:
                    return PickUpType::Regular;
            }
        }

        DropOffType map_drop_off_type(const int data) {
            switch (data) {
                case 1:
                    return DropOffType::Unavailable;
                case 2:
                    return DropOffType::CallAgency;
                case 3:
                    return DropOffType::ContactDriver;
                default:
                    return DropOffType::Regular;
            }
        }

        TimeAccuracy map_time_accuracy(const int data) {
            if (data == 0) return TimeAccuracy::Approximate;
            return TimeAccuracy::Exact;
        }
    }

    std::vector<TripStops> TripStopsLoader::load_trip_stops(const std::string& dataset_directory, size_t trips_count) const {
        csv::CSVReader reader(dataset_directory + "/stop_times.txt");

        const int trip_id_col = reader.index_of("trip_id");
        const int stop_sequence_col = reader.index_of("stop_sequence");
        const int stop_id_col = reader.index_of("stop_id");
        const int arrival_time_col = reader.index_of("arrival_time");
        const int departure_time_col = reader.index_of("departure_time");
        const int pickup_type_col = reader.index_of("pickup_type");
        const int drop_off_type_col = reader.index_of("drop_off_type");
        const int timepoint_col = reader.index_of("timepoint");
        const int shape_dist_traveled_col = reader.index_of("shape_dist_traveled");
        const int fare_units_traveled_col = reader.index_of("fare_units_traveled");

        std::vector<TripStops> trip_stops;
        trip_stops.reserve(trips_count);

        long current_trip_id = -1;
        int current_stop_sequence = -1;
        std::vector<TripStop> current_inner_stops;

        for (auto& row : reader) {
            int stop_sequence = get_safely<int>(row, stop_sequence_col, -1);
            long trip_id = get_safely<long>(row, trip_id_col, -1);

            if (stop_sequence <= current_stop_sequence && current_trip_id == trip_id) {
                throw std::runtime_error("Invalid stop sequence index");
            }

            current_stop_sequence = stop_sequence;

            if (trip_id != current_trip_id) {
                if (!current_inner_stops.empty()) {
                    TripStops new_entry;
                    new_entry.id = current_trip_id;
                    new_entry.stops = current_inner_stops;

                    trip_stops.push_back(std::move(new_entry));
                    current_inner_stops.clear();
                }

                current_trip_id = trip_id;
            }

            TripStop current_trip_stop;

            current_trip_stop.stop_id = get_safely<uint32_t>(row, stop_id_col, 0);
            current_trip_stop.arrival_time = map_time(get_safely<std::string>(row, arrival_time_col, "00:00:00"));
            current_trip_stop.departure_time = map_time(get_safely<std::string>(row, departure_time_col, "00:00:00"));
            current_trip_stop.pickup_type = map_pickup_type(get_safely<int>(row, pickup_type_col, 0));
            current_trip_stop.drop_off_type = map_drop_off_type(get_safely<int>(row, drop_off_type_col, 0));
            current_trip_stop.time_accuracy = map_time_accuracy(get_safely<int>(row, timepoint_col, 1));
            current_trip_stop.shape_dist_traveled = get_safely<uint32_t>(row, shape_dist_traveled_col, 0);
            current_trip_stop.fare_units_traveled = get_safely<uint32_t>(row, fare_units_traveled_col, 0);

            current_inner_stops.push_back(std::move(current_trip_stop));
        }

        if (!current_inner_stops.empty()) {
            TripStops new_entry;
            new_entry.id = current_trip_id;
            new_entry.stops = current_inner_stops;

            trip_stops.push_back(std::move(new_entry));
            current_inner_stops.clear();
        }

        return trip_stops;
    }
}

#pragma once
#include "drop-off-type.h"
#include "pick-up-type.h"
#include "time-accuracy.h"

namespace gtfs {

    struct TripStop {
        uint32_t stop_id{};
        uint32_t arrival_time{};
        uint32_t departure_time{};
        PickUpType pickup_type{PickUpType::Regular};
        DropOffType drop_off_type{DropOffType::Regular};
        TimeAccuracy time_accuracy{TimeAccuracy::Exact};
        uint32_t shape_dist_traveled{};
        uint32_t fare_units_traveled{};
    };
}

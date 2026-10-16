#pragma once

#include <vector>
#include "domain/state/stops/stop.h"

namespace csv {
    class CSVRow;
}

namespace gtfs {

    struct RawStop;

    class StopLoader {

    public:
        static std::vector<Stop> load_stops();

    private:
        static Stop map_no_parent_to_stop(const RawStop& raw_stop);
        static Platform map_to_platform(const RawStop& raw_stop);
        static Platform generate_default_platform(const Stop& stop);
        static std::vector<RawStop> load_raw_stops();
        static WheelchairAccessibility map_wheelchair_accessible(int value);

        template<class T>
        static T get_safely(csv::CSVRow &row, int column_index, T fallback);
    };

}

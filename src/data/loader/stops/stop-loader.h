#pragma once

#include <vector>
#include "domain/state/stops/stop.h"

namespace gtfs {

    struct RawStop;

    class StopLoader {

    public:
        static std::vector<Stop> loadStops();

    private:
        static Stop mapNoParentToStop(const RawStop& raw_stop);
        static Platform mapToPlatform(const RawStop& raw_stop);
        static Platform generateDefaultPlatform(const Stop& stop);
        static std::vector<RawStop> loadRawStops();
    };

}

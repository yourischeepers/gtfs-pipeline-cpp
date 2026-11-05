#pragma once
#include <vector>

#include "domain/state/agencies/routes/route.h"

namespace gtfs {

    class RouteLoader {

    public:
        const std::string fallback_color = "000000";
        const std::string fallback_text_color = "ffffff";

        std::vector<Route> load_routes(const std::string& dataset_directory) const;
    };
}

#pragma once
#include <vector>

#include "../../../../domain/agencies/routes/model/route.h"

namespace gtfs {

    class RouteLoader {

    public:
        const std::string fallback_color = "ffffff";
        const std::string fallback_text_color = "000000";

        std::vector<Route> load_routes(const std::string& dataset_directory) const;
    };
}

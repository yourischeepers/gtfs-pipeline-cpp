#include "route-loader.h"

#include <string>
#include <vector>
#include <csv.hpp>

#include "data/loader/util/color-parser.h"
#include "data/loader/util/csv-util.h"
#include "../../../../domain/agencies/routes/model/route.h"

namespace gtfs {

    std::vector<Route> RouteLoader::load_routes(const std::string& dataset_directory) const {
        csv::CSVReader reader = create_reader(dataset_directory + "/routes.txt");

        const int id_col = reader.index_of("route_id");
        const int agency_id_col = reader.index_of("agency_id");
        const int short_name_col = reader.index_of("route_short_name");
        const int long_name_col = reader.index_of("route_long_name");
        const int color_col = reader.index_of("route_color");
        const int text_color_col = reader.index_of("route_text_color");

        std::vector<Route> routes;

        for (auto& row : reader) {
            Route route;

            route.id = get_safely<long>(row, id_col, -1);
            route.agency_id = get_safely<std::string>(row, agency_id_col, "");
            route.short_name = get_safely<std::string>(row, short_name_col, "");
            route.long_name = get_safely<std::string>(row, long_name_col, "");
            route.color = parse_hex_color(get_safely<std::string>(row, color_col, fallback_color));
            route.text_color = parse_hex_color(get_safely<std::string>(row, text_color_col, fallback_text_color));

            routes.push_back(std::move(route));
        }

        return routes;
    }
}

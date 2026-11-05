#include "agency-loader.h"
#include <csv.hpp>
#include "data/loader/util/csv-util.h"

namespace gtfs {

    std::vector<Agency> AgencyLoader::load_agencies(const std::string &dataset_directory) const {
        csv::CSVReader reader(dataset_directory + "/agency.txt");

        const int id_col = reader.index_of("agency_id");
        const int name_col = reader.index_of("agency_name");
        const int url_col = reader.index_of("agency_url");
        const int timezone_col = reader.index_of("agency_timezone");
        const int phone_col = reader.index_of("agency_phone");

        std::vector<Agency> agencies;

        for (auto& row : reader) {
            Agency agency;

            agency.id = get_safely<std::string>(row, id_col, "");
            agency.name = get_safely<std::string>(row, name_col, "");
            agency.url = get_safely<std::string>(row, url_col, "");
            agency.timezone = time_zone_parser.get_time_zone(get_safely<std::string>(row, timezone_col, ""));
            agency.phone_number = normalize_phone_number(get_safely<std::string>(row, phone_col, ""));

            agencies.push_back(std::move(agency));
        }

        return agencies;
    }

    long AgencyLoader::normalize_phone_number(std::string phone_number) {
        if (phone_number.empty()) return 0;

        if (phone_number.at(0) == '+') phone_number = phone_number.substr(1, phone_number.size() - 1);
        if (size_t pos = phone_number.find('-'); pos != std::string::npos) phone_number.erase(pos, 1);

        return std::stol(phone_number);
    }
}

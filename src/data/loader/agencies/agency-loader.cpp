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
            agency.timezone = time_zone_parser.getTimeZone(get_safely<std::string>(row, timezone_col, ""));
            agency.phone_number = normalize_phonenumber(get_safely<std::string>(row, phone_col, ""));

            agencies.push_back(agency);
        }

        return agencies;
    }

    long AgencyLoader::normalize_phonenumber(std::string phonenumber) {
        if (phonenumber.empty()) return 0;

        if (phonenumber.at(0) == '+') phonenumber = phonenumber.substr(1, phonenumber.size() - 1);
        if (size_t pos = phonenumber.find('-'); pos != std::string::npos) phonenumber.erase(pos, 1);

        return std::stol(phonenumber);
    }
}

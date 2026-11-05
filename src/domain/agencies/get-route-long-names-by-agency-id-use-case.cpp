#include "get-route-long-names-by-agency-id-use-case.h"

namespace gtfs {

    GetRouteLongNamesByAgencyIdUseCase::GetRouteLongNamesByAgencyIdUseCase(const RouteRepository &repository)
        : repository(repository) {}

    std::vector<std::string> GetRouteLongNamesByAgencyIdUseCase::operator()(const std::string &agency_id) const {
        std::vector<std::string> result;

        for (const auto& route : *repository.get_routes()) {
            if (route.agency_id == agency_id) {
                result.push_back(route.long_name);
            }
        }

        return result;
    }
}

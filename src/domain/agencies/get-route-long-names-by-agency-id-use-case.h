#pragma once
#include <string>
#include <vector>

#include "routes/data/route-repository.h"

namespace gtfs {

    class GetRouteLongNamesByAgencyIdUseCase {

    public:
        explicit GetRouteLongNamesByAgencyIdUseCase(const RouteRepository& repository);
        [[nodiscard]] std::vector<std::string> operator()(const std::string& agency_id) const;

    private:
        const RouteRepository& repository;
    };
}

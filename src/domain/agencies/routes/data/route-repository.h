#pragma once
#include <vector>

#include "domain/agencies/routes/model/route.h"

namespace gtfs {

    class RouteRepository {

    public:
        virtual ~RouteRepository() = default;
        [[nodiscard]] virtual std::shared_ptr<const std::vector<Route>> get_routes() const = 0;
    };
}

#pragma once
#include "data/state/memory-state-data-store.h"
#include "domain/agencies/routes/data/route-repository.h"
#include <vector>

namespace gtfs {

    class RouteRepositoryImpl: public RouteRepository {

    public:
        explicit RouteRepositoryImpl(const MemoryStateDataStore& data_store);
        [[nodiscard]] std::shared_ptr<const std::vector<Route>> get_routes() const override;

    private:
        const MemoryStateDataStore& data_store;
    };
}

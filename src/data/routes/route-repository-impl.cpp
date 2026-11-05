#include "route-repository-impl.h"

namespace gtfs {

    RouteRepositoryImpl::RouteRepositoryImpl(const MemoryStateDataStore& data_store)
        : data_store(data_store) {}

    std::shared_ptr<const std::vector<Route>> RouteRepositoryImpl::get_routes() const {
        auto snapshot = data_store.get_current_snapshot();
        return {snapshot, &snapshot->routes};
    }
}

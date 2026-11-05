#include "memory-state-data-store.h"

namespace gtfs {

    MemoryStateDataStore::MemoryStateDataStore(StateSnapshot snapshot) {
        update_current_snapshot(std::move(snapshot));
    }

    void MemoryStateDataStore::update_current_snapshot(StateSnapshot snapshot) {
        auto ptr = std::make_shared<const StateSnapshot>(std::move(snapshot));
        std::lock_guard lock(snapshot_mutex);
        auto old = std::exchange(current_snapshot, std::move(ptr));
    }

    std::shared_ptr<const StateSnapshot> MemoryStateDataStore::get_current_snapshot() const {
        std::lock_guard lock(snapshot_mutex);
        return current_snapshot;
    }
}

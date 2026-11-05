#pragma once
#include <memory>
#include <mutex>

#include "../../domain/state/model/state-snapshot.h"

namespace gtfs {

    class MemoryStateDataStore {

    public:
        explicit MemoryStateDataStore(StateSnapshot snapshot);

        void update_current_snapshot(StateSnapshot snapshot);
        [[nodiscard]] std::shared_ptr<const StateSnapshot> get_current_snapshot() const;

    private:
        mutable std::mutex snapshot_mutex;
        std::shared_ptr<const StateSnapshot> current_snapshot;
    };
}

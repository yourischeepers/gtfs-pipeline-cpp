#pragma once
#include "sync-dataset-use-case.h"
#include "data/dataset-repository.h"

namespace gtfs {

    class CheckForNewDatasetUseCase {

    public:
        explicit CheckForNewDatasetUseCase(
            const DatasetRepository& repository,
            const SyncDatasetUseCase& sync_dataset_use_case
        );
        void operator()() const;

    private:
        const DatasetRepository& repository;
        const SyncDatasetUseCase& sync_dataset_use_case;
    };
}

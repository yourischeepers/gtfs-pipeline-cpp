#include "check-for-new-dataset-use-case.h"

#include <iostream>

namespace gtfs {

    CheckForNewDatasetUseCase::CheckForNewDatasetUseCase(
        const DatasetRepository& repository,
        const SyncDatasetUseCase& sync_dataset_use_case
    )
        : repository(repository)
        , sync_dataset_use_case(sync_dataset_use_case) {}

    void CheckForNewDatasetUseCase::operator()() const {
        const std::string stored = repository.get_stored_e_tag();
        const std::string newest = repository.get_newest_e_tag();

        if (newest != stored) {
            repository.store_e_tag(newest);
            sync_dataset_use_case();
        }
    }
}

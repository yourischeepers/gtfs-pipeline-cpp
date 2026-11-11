#include "sync-dataset-use-case.h"

#include <iostream>

namespace gtfs {

    SyncDatasetUseCase::SyncDatasetUseCase(const DatasetRepository &repository)
        : repository(repository) {}

    void SyncDatasetUseCase::operator()() const {
        // TODO
        std::cout << "Should sync now!" << std::endl;
        repository.download_dataset();
    }
}

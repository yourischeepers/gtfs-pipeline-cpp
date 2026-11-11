#pragma once
#include "data/dataset-repository.h"

namespace gtfs {

    class SyncDatasetUseCase {

    public:
        explicit SyncDatasetUseCase(const DatasetRepository& repository);
        void operator()() const;

    private:
        const DatasetRepository& repository;
    };
}

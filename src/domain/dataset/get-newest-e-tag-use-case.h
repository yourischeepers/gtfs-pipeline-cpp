#pragma once
#include <string>

#include "data/dataset-repository.h"

namespace gtfs {

    class GetNewestETagUseCase {

    public:
        explicit GetNewestETagUseCase(const DatasetRepository& repository);
        [[nodiscard]] std::string operator()() const;

    private:
        const DatasetRepository& repository;
    };
}

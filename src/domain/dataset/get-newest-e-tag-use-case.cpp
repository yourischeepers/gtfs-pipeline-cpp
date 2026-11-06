#include "get-newest-e-tag-use-case.h"

namespace gtfs {

    GetNewestETagUseCase::GetNewestETagUseCase(const DatasetRepository &repository)
        : repository(repository) {}

    std::string GetNewestETagUseCase::operator()() const {
        return repository.get_newest_e_tag();
    }
}

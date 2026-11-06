#include "dataset-repository-impl.h"

namespace gtfs {

    DatasetRepositoryImpl::DatasetRepositoryImpl(const DatasetDataSource& data_source)
        : data_source(data_source) {}

    std::string DatasetRepositoryImpl::get_newest_e_tag() const {
        return data_source.get_newest_e_tag();
    }
}

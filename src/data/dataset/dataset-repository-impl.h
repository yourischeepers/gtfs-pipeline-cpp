#pragma once
#include "dataset-data-source.h"
#include "domain/dataset/data/dataset-repository.h"

namespace gtfs {

    class DatasetRepositoryImpl: public DatasetRepository {

    public:
        explicit DatasetRepositoryImpl(const DatasetDataSource& data_source);
        [[nodiscard]] std::string get_newest_e_tag() const override;
        [[nodiscard]] std::string get_stored_e_tag() const override;
        void store_e_tag(const std::string& etag) const override;

    private:
        const DatasetDataSource& data_source;
    };
}

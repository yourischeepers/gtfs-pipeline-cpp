#pragma once

#include "e-tag-curl-client.h"
#include "data/dataset/dataset-data-source.h"

namespace gtfs {

    class DatasetDataSourceImpl: public DatasetDataSource {

    public:
        [[nodiscard]] std::string get_newest_e_tag() const override;

    private:
        ETagCurlClient client;
    };
}

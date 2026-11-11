#pragma once

#include "dataset-curl-client.h"
#include "e-tag-curl-client.h"
#include "data/dataset/dataset-data-source.h"

namespace gtfs {

    class DatasetDataSourceImpl: public DatasetDataSource {

    public:
        [[nodiscard]] std::string get_newest_e_tag() const override;
        void download_dataset() const override;

    private:
        ETagCurlClient etag_client;
        DatasetCurlClient dataset_client;
    };
}

#include "dataset-data-source-impl.h"

namespace gtfs {

    std::string DatasetDataSourceImpl::get_newest_e_tag() const {
        return etag_client.fetch_e_tag();
    }

    void DatasetDataSourceImpl::download_dataset() const {
        dataset_client.download();
    }
}

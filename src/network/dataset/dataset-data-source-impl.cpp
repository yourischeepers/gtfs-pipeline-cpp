#include "dataset-data-source-impl.h"

namespace gtfs {

    std::string DatasetDataSourceImpl::get_newest_e_tag() const {
        return client.fetch_e_tag();
    }
}

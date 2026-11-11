#include "dataset-repository-impl.h"

#include <fstream>
#include <stdexcept>
#include "data/util/zip/zip-util.h"

namespace gtfs {

    DatasetRepositoryImpl::DatasetRepositoryImpl(const DatasetDataSource& data_source)
        : data_source(data_source) {}

    std::string DatasetRepositoryImpl::get_newest_e_tag() const {
        return data_source.get_newest_e_tag();
    }

    std::string DatasetRepositoryImpl::get_stored_e_tag() const {
        std::ifstream file("./data/etag.txt");
        std::string etag;
        getline(file, etag);
        file.close();
        return etag;
    }

    void DatasetRepositoryImpl::store_e_tag(const std::string& etag) const {
        std::filesystem::create_directories("./data");

        std::ofstream file("./data/etag.txt.tmp");
        file << etag;
        file.close();

        // We do this rename/remove strategy to avoid invalid ETags when a crash occurs during writing
        std::filesystem::rename("./data/etag.txt.tmp", "./data/etag.txt");
    }

    void DatasetRepositoryImpl::download_dataset() const {
        data_source.download_dataset();
    }

    void DatasetRepositoryImpl::unzip_dataset() const {
        unzip("./data/gtfs.zip", "./data/tmp");
        std::filesystem::rename("./data/tmp", "./data/gtfs");
        std::filesystem::remove("./data/gtfs.zip");
    }
}

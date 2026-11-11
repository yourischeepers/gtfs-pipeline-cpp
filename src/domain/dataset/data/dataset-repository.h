#pragma once
#include <string>

namespace gtfs {

    class DatasetRepository {

    public:
        virtual ~DatasetRepository() = default;
        [[nodiscard]] virtual std::string get_newest_e_tag() const = 0;
        [[nodiscard]] virtual std::string get_stored_e_tag() const = 0;
        virtual void store_e_tag(const std::string& etag) const = 0;
        virtual void download_dataset() const = 0;
    };
}

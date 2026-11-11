#pragma once
#include <string>

namespace gtfs {

    class DatasetDataSource {

    public:
        virtual ~DatasetDataSource() = default;
        [[nodiscard]] virtual std::string get_newest_e_tag() const = 0;
        virtual void download_dataset() const = 0;
    };
}

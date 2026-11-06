#pragma once
#include <string>

namespace gtfs {

    class DatasetDataSource {

    public:
        virtual ~DatasetDataSource() = default;
        virtual std::string get_newest_e_tag() const = 0;
    };
}

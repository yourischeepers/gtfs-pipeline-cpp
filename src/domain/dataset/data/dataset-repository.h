#pragma once
#include <string>

namespace gtfs {

    class DatasetRepository {

    public:
        virtual ~DatasetRepository() = default;
        virtual std::string get_newest_e_tag() const = 0;
    };
}

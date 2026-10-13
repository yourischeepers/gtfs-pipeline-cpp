#pragma once

#include <string>

namespace gtfs {

class Platform {

public:
    std::string id;
    std::float_t lat;
    std::float_t lon;
    std::string platformCode;
};

}


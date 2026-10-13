#pragma once

#include <string>
#include <vector>

#include "platform.h"

namespace gtfs {

class Stop {

public:
    std::string id;
    std::string name;
    std::float_t lat;
    std::float_t lon;
    std::string timezone;
    bool wheelchairAccessible;
    std::vector<Platform> platforms;

    void printId();
};

}

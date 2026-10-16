#pragma once

#include <string>

namespace gtfs {

struct Platform {
    std::string id;
    double lat{};
    double lon{};
    std::string platform_code;
};

}


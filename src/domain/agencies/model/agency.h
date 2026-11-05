#pragma once
#include <string>

#include "../../util/timezone.h"

namespace gtfs {

    struct Agency {
        std::string id;
        std::string name;
        std::string url;
        TimeZone timezone{TimeZone::Unknown};
        std::string phone_number;
    };
}

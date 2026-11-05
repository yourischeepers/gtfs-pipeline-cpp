#pragma once
#include <string>

#include "domain/state/general/timezone.h"

namespace gtfs {

    struct Agency {
        std::string id;
        std::string name;
        std::string url;
        TimeZone timezone{TimeZone::Unknown};
        long phone_number{};
    };
}

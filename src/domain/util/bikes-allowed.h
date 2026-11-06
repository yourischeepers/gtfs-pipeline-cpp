#pragma once
#include <cstdint>

namespace gtfs {

    enum class BikesAllowed : std::uint8_t {
        Unknown,
        Allowed,
        NotAllowed,
    };

    BikesAllowed parse_bikes_allowed(const int value);
}
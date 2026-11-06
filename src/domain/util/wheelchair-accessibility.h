#pragma once
#include <cstdint>

namespace gtfs {

    enum class WheelchairAccessibility : std::uint8_t {
        Unknown,
        Accessible,
        NotAccessible,
    };

    WheelchairAccessibility parse_wheelchair_accessibility(const int value);
}

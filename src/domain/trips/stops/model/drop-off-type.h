#pragma once

namespace gtfs {

    enum class DropOffType : uint8_t {
        Regular,
        Unavailable,
        CallAgency,
        ContactDriver,
    };
}

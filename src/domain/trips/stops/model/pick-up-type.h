#pragma once

namespace gtfs {

    enum class PickUpType : uint8_t {
        Regular,
        Unavailable,
        CallAgency,
        ContactDriver,
    };
}

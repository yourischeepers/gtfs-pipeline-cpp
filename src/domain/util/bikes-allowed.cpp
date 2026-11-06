#include "bikes-allowed.h"

namespace gtfs {

    BikesAllowed parse_bikes_allowed(const int value) {
        switch (value) {
            case 1:
                return BikesAllowed::Allowed;
            case 2:
                return BikesAllowed::NotAllowed;
            default:
                return BikesAllowed::Unknown;
        }
    }
}

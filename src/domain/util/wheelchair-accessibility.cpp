#include "wheelchair-accessibility.h"

namespace gtfs {

    WheelchairAccessibility parse_wheelchair_accessibility(const int value) {
        switch (value) {
            case 1:
                return WheelchairAccessibility::Accessible;
            case 2:
                return WheelchairAccessibility::NotAccessible;
            default:
                return WheelchairAccessibility::Unknown;
        }
    }
}

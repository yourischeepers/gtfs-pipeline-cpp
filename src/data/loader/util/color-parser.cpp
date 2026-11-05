#include "data/loader/util/color-parser.h"

namespace gtfs {

    Color parse_hex_color(const std::string& hex) {
        auto data = std::stoul(hex, nullptr, 16);
        Color color;

        color.r = (data >> 16) & 0xFF;
        color.g = (data >> 8) & 0xFF;
        color.b = data & 0xFF;

        return color;
    }
}
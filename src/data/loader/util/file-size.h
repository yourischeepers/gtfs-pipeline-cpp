#pragma once

#include <string>

namespace gtfs {

    [[nodiscard]] std::uintmax_t get_file_size_bytes(const std::string& path);
}

#include "file-size.h"

#include <filesystem>

namespace gtfs {

    std::uintmax_t get_file_size_bytes(const std::string& path) {
        return std::filesystem::file_size(std::filesystem::path(path));
    }
}

#include "zip-util.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <zip.h>

namespace gtfs {

    void unzip(const std::string& source, const std::string& destination) {
        zip_t* archive = zip_open(source.c_str(), ZIP_RDONLY, nullptr);
        if (archive == nullptr) throw std::runtime_error("Unzip failed: " + source);

        std::filesystem::create_directories(destination);
        std::vector<char> buffer(1 << 20);

        for (zip_uint64_t i = 0; i < static_cast<zip_uint64_t>(zip_get_num_entries(archive, 0)); i++) {
            zip_file_t* file = zip_fopen_index(archive, i, 0);
            std::ofstream out(std::filesystem::path(destination) / zip_get_name(archive, i, 0), std::ios::binary);

            zip_int64_t bytes_read;
            while ((bytes_read = zip_fread(file, buffer.data(), buffer.size())) > 0) {
                out.write(buffer.data(), bytes_read);
            }

            zip_fclose(file);
        }

        zip_close(archive);
    }
}

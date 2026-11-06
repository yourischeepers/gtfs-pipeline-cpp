#include "csv-util.h"

namespace gtfs {

    csv::CSVReader create_reader(const std::string &file_path) {
        csv::CSVFormat format;
        format.chunk_size(1 << 20);
        return csv::CSVReader(file_path, format);
    }
}

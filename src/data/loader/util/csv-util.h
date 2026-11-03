#pragma once

#include <csv.hpp>

namespace gtfs {

    template <typename T>
    T get_safely(
        const csv::CSVRow& row,
        int column_index,
        T fallback
    ) {
        if (column_index < 0) return fallback;

        auto field = row[column_index];
        if (field.is_null()) return fallback;

        return field.get<T>();
    }
}
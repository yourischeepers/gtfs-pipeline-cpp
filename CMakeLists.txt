cmake_minimum_required(VERSION 3.25)

project(gtfs_pipeline_cpp
        VERSION 0.1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Protobuf CONFIG REQUIRED)
find_package(unofficial-vincentlaucsb-csv-parser CONFIG REQUIRED)

add_executable(gtfs_pipeline
        src/main.cpp
)

target_link_libraries(gtfs_pipeline
        PRIVATE
        protobuf::libprotobuf
        unofficial::vincentlaucsb-csv-parser::csv
)
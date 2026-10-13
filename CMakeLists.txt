cmake_minimum_required(VERSION 3.25)

project(gtfs_pipeline_cpp
        VERSION 0.1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(gtfs_pipeline ${SOURCES})

target_include_directories(gtfs_pipeline PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

find_package(Protobuf CONFIG REQUIRED)
find_package(unofficial-vincentlaucsb-csv-parser CONFIG REQUIRED)

target_link_libraries(gtfs_pipeline
        PRIVATE
        protobuf::libprotobuf
        unofficial::vincentlaucsb-csv-parser::csv
)
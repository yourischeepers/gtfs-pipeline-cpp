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

find_package(Protobuf CONFIG REQUIRED)
find_package(unofficial-vincentlaucsb-csv-parser CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(libzip CONFIG REQUIRED)

add_executable(gtfs_pipeline ${SOURCES})
target_compile_options(gtfs_pipeline PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)

target_include_directories(gtfs_pipeline PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(gtfs_pipeline
        PRIVATE
        protobuf::libprotobuf
        unofficial::vincentlaucsb-csv-parser::csv
        CURL::libcurl
        libzip::zip
)
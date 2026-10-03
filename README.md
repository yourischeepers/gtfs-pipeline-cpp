# gtfs-pipeline-cpp

A small C++ project for ingesting, normalizing, and querying Dutch public transport data using GTFS and GTFS-Realtime.

The project is primarily a learning project focused on modern C++, systems programming, data processing, and performance engineering.

## Goals

- Learn modern C++ through a real-world data processing problem
- Parse GTFS-Realtime Protobuf feeds
- Load static GTFS reference data
- Normalize raw transport data into an internal domain model
- Maintain a live in-memory view of vehicles and trips
- Measure and improve processing performance
- Explore memory usage, data structures, concurrency, and cache behavior

## Initial scope

The first version will:

1. Decode a real GTFS-Realtime Protobuf message
2. Inspect vehicle positions and trip updates
3. Convert Protobuf messages into a small internal C++ model
4. Load relevant static GTFS data
5. Connect realtime updates to static trip, route, and stop information
6. Maintain normalized state in memory

Later versions may expose a small HTTP API and include performance benchmarks.

## Architecture

```text
              Static GTFS
                   |
                   v
          +------------------+
          | StaticGtfsLoader |
          +------------------+
                   |
                   v
          +------------------+
          | TransitReference |
          +------------------+
                   ^
                   |
                   |
GTFS-Realtime      |
Protobuf feed      |
      |            |
      v            |
+----------------+ |
| RealtimeParser | |
+----------------+ |
      |            |
      v            |
+--------------------+
| RealtimeNormalizer |
+--------------------+
          |
          v
   +--------------+
   | TransitState |
   +--------------+
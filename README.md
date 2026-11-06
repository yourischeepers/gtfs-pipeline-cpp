# gtfs-pipeline-cpp

A C++20 project that loads the Dutch public transport schedule (GTFS) into memory and makes it queryable. It is a learning project, built to practice modern C++, memory and performance engineering, concurrency-safe design, and clean layering without a DI framework.

The static schedule loads today (about 21 million stop times in roughly 4 seconds, ~0.84 GiB of RAM). Dataset syncing, GTFS-Realtime and an API are still to come, see [Status](#status).

## Status

| Area | State |
|---|---|
| Static GTFS loading: agencies, routes, stops (with platforms), trips, stop times | Done |
| Immutable in-memory snapshot with atomic swap | Done |
| Route repository + use case "route names of an agency" | Done |
| Memory optimization of the load (peak ~1.7 GiB down to ~0.84 GiB) | Done |
| Fetch the dataset's current `ETag` with libcurl (`HEAD` request) | Done |
| Persist the `ETag`, scheduled check twice a day | Next |
| Download, unzip and reload the dataset when the `ETag` changed | Next |
| GTFS-Realtime (Protobuf) parsing and a live state | Planned (the Protobuf library is linked but not used yet) |
| Public API (REST, or a gRPC core behind a gateway) | Planned |
| Service calendar (`calendar_dates.txt`), `shapes.txt` | Not loaded yet |
| Automated tests | None yet |
| Linux / Docker | Not tested yet |

Note: `src/main.cpp` currently runs the `ETag` check only. The code that loads the dataset and queries it is commented out while the sync flow is being built, see [Running](#running).

## Dataset

Developed against the [OVapi](https://gtfs.ovapi.nl/) Dutch national feed (`gtfs-nl.zip`, roughly 200-250 MiB zipped depending on the version, ~1.6 GB unzipped). The version used for the numbers below:

| Entity | Count |
|---|---|
| Stops (without a parent station) | 52,802 |
| Agencies | 40 |
| Routes | 3,487 |
| Trips | 1,073,682 |
| Stop times | 20,910,070 (`stop_times.txt` is 1.2 GB) |

Measured in a Release build on an Apple Silicon MacBook: the whole dataset loads in about 4 seconds, with a peak resident memory of about 857 MiB (877,376 KiB).

## Architecture

The code is split in three layers. Dependencies point inwards, so the domain knows nothing about files, CSV, curl or any transport.

```mermaid
flowchart LR
    main["main (wires everything together)"]
    domain["domain: models, use cases, repository interfaces"]
    data["data: loaders, state store, repository implementations"]
    network["network: libcurl client"]

    main --> domain
    main --> data
    main --> network
    data --> domain
    network --> data
```

- **`domain/`**: plain data models (`Agency`, `Route`, `Stop`, `Trip`, `TripStop`...), the `StateSnapshot`, repository interfaces, and use cases (`GetRouteLongNamesByAgencyIdUseCase`, `GetNewestETagUseCase`). Use cases are callable objects (`operator()`), one per file.
- **`data/`**: the GTFS loaders (CSV to domain models), the `MemoryStateDataStore`, and the repository implementations. Where the data comes from over the network, it depends on a small interface (`DatasetDataSource`) instead of curl.
- **`network/`**: the libcurl implementation of that interface (an RAII client that fetches the `ETag` header).
- **Wiring** is manual constructor injection in `main.cpp`. There is no DI framework; the constructors take references to interfaces, so a fake can be passed in tests.

### The state store

`MemoryStateDataStore` holds a `std::shared_ptr<const StateSnapshot>`. The snapshot is built completely and never modified afterwards.

- Readers call `get_current_snapshot()` and keep the returned pointer for as long as they need a consistent view. The repository returns pointers into the snapshot using the `shared_ptr` aliasing constructor, so the snapshot stays alive while they are used.
- A reload builds a new snapshot in the background, then swaps the pointer. Requests in flight keep using the old one, which is freed when the last reader lets go.
- The lock only guards copying the pointer, and the old snapshot is destroyed outside the lock so readers never wait on a large deallocation.

## Interesting challenges and trade-offs

**Memory: 1.2 GB of stop times in under 1 GiB.** The first working version needed about 1.7 GiB. Measuring first (parse-only experiments, `heap`/RSS numbers) showed where it went:
- The CSV library reads in 10 MB chunks by default, which cost about 640 MB of peak memory on this dataset. Using a 1 MB chunk saves that with no change in parse speed.
- `TripStop` shrank from 48 to 24 bytes by using `uint32_t` ids and times (seconds since the start of the service day) and 1-byte enums, with the fields ordered to avoid padding. Each type was checked against the real maximum in the data: for example `fare_units_traveled` reaches 336,560, so it cannot be a `uint16_t`.
- Each trip's stops are copied into an exact-size vector instead of moved from the growing scratch buffer. Moving keeps the vector's growth slack and cost about 170 MB more across 1M trips.
- The trips vector is reserved from a row estimate based on the file size (and the per-trip list from the trip count), so the large vectors are allocated once instead of doubling and copying.

**An immutable snapshot instead of locks around mutable data.** A daily reload must not block readers or expose half-loaded data. The `libc++` shipped with Apple clang does not provide `std::atomic<std::shared_ptr>`, so the swap uses a mutex that only guards the pointer. During a reload the old and the new data will exist at the same time, so the peak will be roughly twice the steady-state memory.

**GTFS has many details.** Times can go beyond `24:00:00` (over 577,000 rows here) for trips past midnight; `stop_sequence` is increasing but not consecutive; stops have a parent/platform hierarchy; optional fields have spec-defined defaults (for example route colors). The stop times loader relies on the file being grouped by trip and checks that `stop_sequence` strictly increases within a trip (it throws otherwise). The grouping itself is an assumption that holds for this feed.

**Cheap change detection.** The server supports `ETag` and conditional requests (`If-None-Match` returns `304 Not Modified`), so checking for a new dataset does not need to download the 200 MB file.

**C++ details learned along the way.** RAII for C handles (`unique_ptr` with a custom deleter, rule of zero), typed wrappers around variadic C APIs (`curl_easy_setopt` takes exact types), range-for lifetime pitfalls with temporaries, and writing interfaces with pure virtual functions.

## Tech stack

- C++20, CMake (3.25+), [vcpkg](https://github.com/microsoft/vcpkg) in manifest mode
- [vincentlaucsb-csv-parser](https://github.com/vincentlaucsb/csv-parser) for CSV parsing
- libcurl for HTTP
- Protobuf (linked for the upcoming GTFS-Realtime work, not used yet)
- Compiled with `-Wall -Wextra -Wpedantic -Wshadow -Wconversion`

## Building

Prerequisites: CMake 3.25 or newer, a C++20 compiler, and vcpkg. Developed on macOS (Apple Silicon, Apple clang). Linux has not been tested yet.

```bash
# Once: point to your vcpkg checkout
export VCPKG_ROOT=/path/to/vcpkg

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build build
```

vcpkg installs the dependencies listed in `vcpkg.json` during the configure step. The first run can take several minutes when nothing is cached. Use `Release` for realistic memory and speed numbers; a Debug build is much slower (loading takes about ten times as long).

## Getting the data

The dataset is not part of the repository (`data/` is git-ignored). Download and unzip it so the `.txt` files end up in `data/gtfs`:

```bash
mkdir -p data/gtfs
curl -L -o data/gtfs-nl.zip https://gtfs.ovapi.nl/nl/gtfs-nl.zip
unzip data/gtfs-nl.zip -d data/gtfs
```

The zip is roughly 200-250 MiB and about 1.6 GB when unzipped.

## Running

```bash
cd build
./gtfs_pipeline
```

As it is now, this prints the dataset's current `ETag` (`Found ETag "..."`) and needs internet access.

To try the loading and the query use case, uncomment the block at the top of `main()` in `src/main.cpp`. It asks for the dataset directory (default `../data/gtfs`, relative to where you run it, so run it from `build/`), loads everything, prints the route names of agency `GVB`, and prints the peak memory. That memory number uses `getrusage`, whose unit differs between macOS (bytes) and Linux (KiB); it is only correct on macOS for now.

## Known limitations

- Malformed values stop the load with an exception; there is no per-row error policy yet. The CSV library silently skips rows with the wrong number of columns by default.
- Optional values that are empty in the data (such as `shape_dist_traveled`) are stored as `0`, so "unknown" and `0` look the same.
- Only the Dutch OVapi feed has been tried.

## Roadmap

1. Store the last loaded `ETag` in a file, compare on a schedule (twice a day).
2. Download, unzip, load and swap the snapshot; delete the temporary files.
3. GTFS-Realtime: parse the Protobuf feeds and keep a live state next to the static snapshot.
4. Expose the data through an API (REST, or gRPC between a gateway and this core).
5. Load the service calendar so trips can be filtered by date, add tests, and try Linux/Docker.

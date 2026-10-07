# Student Records System

A modular, console-based student records application written in C++20. The initial implementation stores records in memory and supports adding, viewing, listing, updating, and deleting students.

## Requirements

- CMake 3.20 or newer
- A C++20 compiler (GCC 11+, Clang 14+, or MSVC 2022+ recommended)
- Network access during the first test-enabled CMake configure, so CMake FetchContent can retrieve GoogleTest

## Build and run

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/student_records_app
```

On multi-configuration generators such as Visual Studio, the executable may be under `build/Release/`.

## Run tests

```sh
ctest --test-dir build --output-on-failure
```

To build the application without downloading GoogleTest:

```sh
cmake -S . -B build -DSTUDENT_RECORDS_BUILD_TESTS=OFF
cmake --build build
```

## Validation and behavior

- Student IDs are non-empty and unique.
- Email addresses must match the application's basic email format and be unique.
- Names and course are required.
- Year of study must be between 1 and 8.
- Enrollment status is one of `Active`, `Inactive`, `Suspended`, or `Graduated`.
- Data is held in memory and is lost when the process exits; persistent storage is not part of this version.

## Layout

- `include/domain/`: student entity and enrollment status
- `include/repository/`: repository contract and in-memory implementation
- `include/service/`: business rules
- `include/validation/`: input validation
- `include/logging/`: logger contract and console logger
- `include/exceptions/`: application exception hierarchy
- `include/ui/`: console user interface
- `src/`: implementations and application entry point
- `tests/`: GoogleTest unit tests

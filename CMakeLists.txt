cmake_minimum_required(VERSION 3.20)
project(StudentRecordsApp VERSION 1.0.0 LANGUAGES CXX)

option(STUDENT_RECORDS_BUILD_TESTS "Build unit tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(student_core
    src/domain/EnrollmentStatus.cpp
    src/logging/ConsoleLogger.cpp
    src/repository/StudentRepository.cpp
    src/service/StudentService.cpp
    src/ui/ConsoleUI.cpp
    src/validation/Validator.cpp
)
target_include_directories(student_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    target_compile_options(student_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(student_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(student_records_app src/main.cpp)
target_link_libraries(student_records_app PRIVATE student_core)

if(STUDENT_RECORDS_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    # Prevent GoogleTest from overriding the parent project's compiler/linker settings on Windows.
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    add_subdirectory(tests)
endif()

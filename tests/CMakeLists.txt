add_executable(unit_tests
    StudentRepositoryTests.cpp
    StudentServiceTests.cpp
    ValidatorTests.cpp
)
target_link_libraries(unit_tests PRIVATE student_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)

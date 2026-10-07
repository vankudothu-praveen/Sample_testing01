#include "exceptions/Exceptions.hpp"
#include "validation/Validator.hpp"

#include <gtest/gtest.h>

using namespace studentapp;

namespace {
Student validStudent() {
    return {"1", "John", "Doe", "john@example.com", "CS", 2, EnrollmentStatus::Active};
}
}

TEST(ValidatorTests, ValidStudentPassesValidation) {
    EXPECT_NO_THROW(Validator::validateStudent(validStudent()));
}

TEST(ValidatorTests, InvalidEmailThrows) {
    auto student = validStudent();
    student.email = "invalid";
    EXPECT_THROW(Validator::validateStudent(student), ValidationException);
}

TEST(ValidatorTests, EmptyNameThrows) {
    auto student = validStudent();
    student.firstName.clear();
    EXPECT_THROW(Validator::validateStudent(student), ValidationException);
}

TEST(ValidatorTests, YearOutsideSupportedRangeThrows) {
    auto student = validStudent();
    student.yearOfStudy = 9;
    EXPECT_THROW(Validator::validateStudent(student), ValidationException);
}

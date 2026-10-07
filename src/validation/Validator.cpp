#include "validation/Validator.hpp"

#include "exceptions/Exceptions.hpp"

#include <regex>

namespace studentapp {
namespace {
const std::regex EMAIL_REGEX(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
}

void Validator::validateStudent(const Student& student) {
    validateStudentId(student.studentId);
    validateName(student.firstName, "First name");
    validateName(student.lastName, "Last name");
    validateEmail(student.email);
    validateCourse(student.course);
    validateYear(student.yearOfStudy);
    validateEnrollmentStatus(student.enrollmentStatus);
}

void Validator::validateStudentId(const std::string& studentId) {
    if (studentId.empty()) throw ValidationException("Student ID cannot be empty");
}

void Validator::validateName(const std::string& value, const std::string& fieldName) {
    if (value.empty()) throw ValidationException(fieldName + " cannot be empty");
}

void Validator::validateEmail(const std::string& email) {
    if (!std::regex_match(email, EMAIL_REGEX)) throw ValidationException("Invalid email format");
}

void Validator::validateCourse(const std::string& course) {
    if (course.empty()) throw ValidationException("Course cannot be empty");
}

void Validator::validateYear(std::uint16_t year) {
    if (year == 0U || year > 8U) throw ValidationException("Year of study must be between 1 and 8");
}

void Validator::validateEnrollmentStatus(EnrollmentStatus status) {
    switch (status) {
        case EnrollmentStatus::Active:
        case EnrollmentStatus::Inactive:
        case EnrollmentStatus::Suspended:
        case EnrollmentStatus::Graduated:
            return;
    }
    throw ValidationException("Invalid enrollment status");
}

} // namespace studentapp

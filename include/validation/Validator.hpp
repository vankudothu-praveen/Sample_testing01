#pragma once

#include "domain/Student.hpp"

namespace studentapp {

class Validator {
public:
    static void validateStudent(const Student& student);

private:
    static void validateStudentId(const std::string& studentId);
    static void validateName(const std::string& value, const std::string& fieldName);
    static void validateEmail(const std::string& email);
    static void validateCourse(const std::string& course);
    static void validateYear(std::uint16_t year);
    static void validateEnrollmentStatus(EnrollmentStatus status);
};

} // namespace studentapp

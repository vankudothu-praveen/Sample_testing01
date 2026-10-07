#pragma once

#include "domain/EnrollmentStatus.hpp"

#include <cstdint>
#include <string>

namespace studentapp {

struct Student {
    std::string studentId;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string course;
    std::uint16_t yearOfStudy{};
    EnrollmentStatus enrollmentStatus{EnrollmentStatus::Active};
};

} // namespace studentapp

#include "domain/EnrollmentStatus.hpp"

#include "exceptions/Exceptions.hpp"

#include <algorithm>
#include <array>
#include <cctype>

namespace studentapp {

std::string toString(EnrollmentStatus status) {
    switch (status) {
        case EnrollmentStatus::Active: return "Active";
        case EnrollmentStatus::Inactive: return "Inactive";
        case EnrollmentStatus::Suspended: return "Suspended";
        case EnrollmentStatus::Graduated: return "Graduated";
    }
    throw ValidationException("Unknown enrollment status");
}

EnrollmentStatus enrollmentStatusFromString(std::string_view value) {
    std::string normalized(value);
    std::transform(normalized.begin(), normalized.end(), normalized.begin(),
                   [](unsigned char character) { return static_cast<char>(std::tolower(character)); });

    if (normalized == "active") return EnrollmentStatus::Active;
    if (normalized == "inactive") return EnrollmentStatus::Inactive;
    if (normalized == "suspended") return EnrollmentStatus::Suspended;
    if (normalized == "graduated") return EnrollmentStatus::Graduated;
    throw ValidationException("Status must be Active, Inactive, Suspended, or Graduated");
}

} // namespace studentapp

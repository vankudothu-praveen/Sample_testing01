#pragma once

#include <string>
#include <string_view>

namespace studentapp {

enum class EnrollmentStatus {
    Active,
    Inactive,
    Suspended,
    Graduated
};

[[nodiscard]] std::string toString(EnrollmentStatus status);
[[nodiscard]] EnrollmentStatus enrollmentStatusFromString(std::string_view value);

} // namespace studentapp

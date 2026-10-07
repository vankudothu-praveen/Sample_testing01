#pragma once

#include "domain/Student.hpp"

#include <optional>
#include <string_view>
#include <vector>

namespace studentapp {

class IStudentRepository {
public:
    virtual ~IStudentRepository() = default;
    virtual void addStudent(const Student& student) = 0;
    [[nodiscard]] virtual std::optional<Student> getStudentById(std::string_view studentId) const = 0;
    virtual void updateStudent(const Student& student) = 0;
    virtual void deleteStudent(std::string_view studentId) = 0;
    [[nodiscard]] virtual std::vector<Student> getAllStudents() const = 0;
};

} // namespace studentapp

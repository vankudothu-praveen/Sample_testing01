#pragma once

#include "repository/IStudentRepository.hpp"

#include <shared_mutex>
#include <string>
#include <unordered_map>

namespace studentapp {

class StudentRepository final : public IStudentRepository {
public:
    void addStudent(const Student& student) override;
    [[nodiscard]] std::optional<Student> getStudentById(std::string_view studentId) const override;
    void updateStudent(const Student& student) override;
    void deleteStudent(std::string_view studentId) override;
    [[nodiscard]] std::vector<Student> getAllStudents() const override;

private:
    std::unordered_map<std::string, Student> students_;
    mutable std::shared_mutex mutex_;
};

} // namespace studentapp

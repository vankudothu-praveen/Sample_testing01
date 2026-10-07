#pragma once

#include "logging/ILogger.hpp"
#include "repository/IStudentRepository.hpp"

#include <memory>
#include <string>
#include <vector>

namespace studentapp {

class StudentService {
public:
    StudentService(std::shared_ptr<IStudentRepository> repository,
                   std::shared_ptr<ILogger> logger);

    void addStudent(const Student& student);
    [[nodiscard]] Student getStudentById(const std::string& studentId) const;
    [[nodiscard]] std::vector<Student> getAllStudents() const;
    void updateStudent(const Student& student);
    void deleteStudent(const std::string& studentId);

private:
    std::shared_ptr<IStudentRepository> repository_;
    std::shared_ptr<ILogger> logger_;
};

} // namespace studentapp

#include "repository/StudentRepository.hpp"

#include "exceptions/Exceptions.hpp"

#include <mutex>

namespace studentapp {

void StudentRepository::addStudent(const Student& student) {
    std::unique_lock lock(mutex_);
    const auto [iterator, inserted] = students_.emplace(student.studentId, student);
    (void)iterator;
    if (!inserted) {
        throw DuplicateStudentException("Student ID already exists: " + student.studentId);
    }
}

std::optional<Student> StudentRepository::getStudentById(std::string_view studentId) const {
    std::shared_lock lock(mutex_);
    const auto iterator = students_.find(std::string(studentId));
    if (iterator == students_.end()) return std::nullopt;
    return iterator->second;
}

void StudentRepository::updateStudent(const Student& student) {
    std::unique_lock lock(mutex_);
    const auto iterator = students_.find(student.studentId);
    if (iterator == students_.end()) {
        throw StudentNotFoundException("Student not found: " + student.studentId);
    }
    iterator->second = student;
}

void StudentRepository::deleteStudent(std::string_view studentId) {
    std::unique_lock lock(mutex_);
    if (students_.erase(std::string(studentId)) == 0U) {
        throw StudentNotFoundException("Student not found: " + std::string(studentId));
    }
}

std::vector<Student> StudentRepository::getAllStudents() const {
    std::shared_lock lock(mutex_);
    std::vector<Student> students;
    students.reserve(students_.size());
    for (const auto& [id, student] : students_) {
        (void)id;
        students.push_back(student);
    }
    return students;
}

} // namespace studentapp

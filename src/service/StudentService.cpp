#include "service/StudentService.hpp"

#include "exceptions/Exceptions.hpp"
#include "validation/Validator.hpp"

#include <utility>

namespace studentapp {

StudentService::StudentService(std::shared_ptr<IStudentRepository> repository,
                               std::shared_ptr<ILogger> logger)
    : repository_(std::move(repository)), logger_(std::move(logger)) {
    if (!repository_) throw ApplicationException("Student repository must not be null");
    if (!logger_) throw ApplicationException("Logger must not be null");
}

void StudentService::addStudent(const Student& student) {
    Validator::validateStudent(student);
    for (const auto& existing : repository_->getAllStudents()) {
        if (existing.email == student.email) {
            throw DuplicateStudentException("Email already exists: " + student.email);
        }
    }
    repository_->addStudent(student);
    logger_->logInfo("Student added: " + student.studentId);
}

Student StudentService::getStudentById(const std::string& studentId) const {
    const auto student = repository_->getStudentById(studentId);
    if (!student) throw StudentNotFoundException("Student not found: " + studentId);
    return *student;
}

std::vector<Student> StudentService::getAllStudents() const {
    return repository_->getAllStudents();
}

void StudentService::updateStudent(const Student& student) {
    Validator::validateStudent(student);
    // Confirm existence before checking email so a missing ID has a clear error.
    (void)getStudentById(student.studentId);
    for (const auto& existing : repository_->getAllStudents()) {
        if (existing.studentId != student.studentId && existing.email == student.email) {
            throw DuplicateStudentException("Email already exists: " + student.email);
        }
    }
    repository_->updateStudent(student);
    logger_->logInfo("Student updated: " + student.studentId);
}

void StudentService::deleteStudent(const std::string& studentId) {
    repository_->deleteStudent(studentId);
    logger_->logInfo("Student deleted: " + studentId);
}

} // namespace studentapp

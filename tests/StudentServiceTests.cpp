#include "exceptions/Exceptions.hpp"
#include "logging/ILogger.hpp"
#include "repository/StudentRepository.hpp"
#include "service/StudentService.hpp"

#include <gtest/gtest.h>
#include <memory>

using namespace studentapp;

namespace {
class TestLogger final : public ILogger {
public:
    void logInfo(const std::string&) override {}
    void logWarning(const std::string&) override {}
    void logError(const std::string&) override {}
};

Student sampleStudent(std::string id, std::string email) {
    return {std::move(id), "John", "Doe", std::move(email), "CS", 1, EnrollmentStatus::Active};
}
}

TEST(StudentServiceTests, AddAndRetrieveStudent) {
    auto repository = std::make_shared<StudentRepository>();
    StudentService service(repository, std::make_shared<TestLogger>());
    service.addStudent(sampleStudent("1", "john@example.com"));
    EXPECT_EQ(service.getStudentById("1").email, "john@example.com");
}

TEST(StudentServiceTests, DuplicateEmailThrows) {
    auto repository = std::make_shared<StudentRepository>();
    StudentService service(repository, std::make_shared<TestLogger>());
    service.addStudent(sampleStudent("1", "john@example.com"));
    EXPECT_THROW(service.addStudent(sampleStudent("2", "john@example.com")), DuplicateStudentException);
}

TEST(StudentServiceTests, DuplicateEmailOnUpdateThrows) {
    auto repository = std::make_shared<StudentRepository>();
    StudentService service(repository, std::make_shared<TestLogger>());
    service.addStudent(sampleStudent("1", "john@example.com"));
    service.addStudent(sampleStudent("2", "jane@example.com"));
    EXPECT_THROW(service.updateStudent(sampleStudent("2", "john@example.com")), DuplicateStudentException);
}

TEST(StudentServiceTests, DeleteMissingStudentThrows) {
    auto repository = std::make_shared<StudentRepository>();
    StudentService service(repository, std::make_shared<TestLogger>());
    EXPECT_THROW(service.deleteStudent("missing"), StudentNotFoundException);
}

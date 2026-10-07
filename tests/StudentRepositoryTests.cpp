#include "exceptions/Exceptions.hpp"
#include "repository/StudentRepository.hpp"

#include <gtest/gtest.h>

using namespace studentapp;

namespace {
Student sampleStudent() {
    return {"1", "John", "Doe", "john@example.com", "CS", 1, EnrollmentStatus::Active};
}
}

TEST(StudentRepositoryTests, AddAndRetrieveStudent) {
    StudentRepository repository;
    repository.addStudent(sampleStudent());
    const auto result = repository.getStudentById("1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->firstName, "John");
}

TEST(StudentRepositoryTests, MissingStudentReturnsEmptyOptional) {
    StudentRepository repository;
    EXPECT_FALSE(repository.getStudentById("missing").has_value());
}

TEST(StudentRepositoryTests, DuplicateStudentIdThrows) {
    StudentRepository repository;
    repository.addStudent(sampleStudent());
    EXPECT_THROW(repository.addStudent(sampleStudent()), DuplicateStudentException);
}

TEST(StudentRepositoryTests, UpdateAndDeleteStudent) {
    StudentRepository repository;
    auto student = sampleStudent();
    repository.addStudent(student);
    student.firstName = "Jane";
    repository.updateStudent(student);
    ASSERT_TRUE(repository.getStudentById("1").has_value());
    EXPECT_EQ(repository.getStudentById("1")->firstName, "Jane");
    repository.deleteStudent("1");
    EXPECT_FALSE(repository.getStudentById("1").has_value());
}

TEST(StudentRepositoryTests, UpdateMissingStudentThrows) {
    StudentRepository repository;
    EXPECT_THROW(repository.updateStudent(sampleStudent()), StudentNotFoundException);
}

TEST(StudentRepositoryTests, DeleteMissingStudentThrows) {
    StudentRepository repository;
    EXPECT_THROW(repository.deleteStudent("missing"), StudentNotFoundException);
}

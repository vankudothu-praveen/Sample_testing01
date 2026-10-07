#pragma once

#include <stdexcept>
#include <string>

namespace studentapp {

class ApplicationException : public std::runtime_error {
public:
    explicit ApplicationException(const std::string& message) : std::runtime_error(message) {}
};

class ValidationException : public ApplicationException {
public:
    explicit ValidationException(const std::string& message) : ApplicationException(message) {}
};

class DuplicateStudentException : public ApplicationException {
public:
    explicit DuplicateStudentException(const std::string& message) : ApplicationException(message) {}
};

class StudentNotFoundException : public ApplicationException {
public:
    explicit StudentNotFoundException(const std::string& message) : ApplicationException(message) {}
};

class RepositoryException : public ApplicationException {
public:
    explicit RepositoryException(const std::string& message) : ApplicationException(message) {}
};

} // namespace studentapp

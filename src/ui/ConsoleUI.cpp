#include "ui/ConsoleUI.hpp"

#include "domain/EnrollmentStatus.hpp"
#include "exceptions/Exceptions.hpp"

#include <iostream>
#include <limits>
#include <sstream>

namespace studentapp {

ConsoleUI::ConsoleUI(StudentService& service) : service_(service) {}

std::string ConsoleUI::readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    if (!std::getline(std::cin, value)) return {};
    return value;
}

std::uint16_t ConsoleUI::readYear() {
    while (true) {
        const std::string input = readLine("Year of Study (1-8): ");
        unsigned int value{};
        std::istringstream stream(input);
        char trailing{};
        if ((stream >> value) && !(stream >> trailing) && value >= 1U && value <= 8U) {
            return static_cast<std::uint16_t>(value);
        }
        if (!std::cin) return 0;
        std::cerr << "Please enter a whole number from 1 to 8.\n";
    }
}

Student ConsoleUI::inputStudentData(const std::string& studentId) {
    Student student;
    student.studentId = studentId.empty() ? readLine("Student ID: ") : studentId;
    student.firstName = readLine("First Name: ");
    student.lastName = readLine("Last Name: ");
    student.email = readLine("Email: ");
    student.course = readLine("Course: ");
    student.yearOfStudy = readYear();
    std::cout << "Enrollment Status (Active/Inactive/Suspended/Graduated) [Active]: ";
    std::string status;
    if (!std::getline(std::cin, status)) status.clear();
    student.enrollmentStatus = status.empty() ? EnrollmentStatus::Active : enrollmentStatusFromString(status);
    return student;
}

void ConsoleUI::displayMenu() const {
    std::cout << "\nStudent Records System\n"
              << "1. Add Student\n"
              << "2. View Student\n"
              << "3. List Students\n"
              << "4. Update Student\n"
              << "5. Delete Student\n"
              << "0. Exit\n";
}

void ConsoleUI::handleAddStudent() {
    try {
        service_.addStudent(inputStudentData());
        std::cout << "Student added successfully.\n";
    } catch (const ApplicationException& exception) {
        std::cerr << exception.what() << '\n';
    }
}

void ConsoleUI::handleViewStudent() {
    try {
        const auto student = service_.getStudentById(readLine("Student ID: "));
        std::cout << student.studentId << " | " << student.firstName << ' ' << student.lastName
                  << " | " << student.email << " | " << student.course
                  << " | Year " << student.yearOfStudy << " | " << toString(student.enrollmentStatus) << '\n';
    } catch (const ApplicationException& exception) {
        std::cerr << exception.what() << '\n';
    }
}

void ConsoleUI::handleListStudents() {
    const auto students = service_.getAllStudents();
    if (students.empty()) {
        std::cout << "No student records found.\n";
        return;
    }
    for (const auto& student : students) {
        std::cout << student.studentId << " | " << student.firstName << ' ' << student.lastName
                  << " | " << student.email << " | " << student.course
                  << " | Year " << student.yearOfStudy << " | " << toString(student.enrollmentStatus) << '\n';
    }
}

void ConsoleUI::handleUpdateStudent() {
    try {
        const std::string id = readLine("Student ID to update: ");
        (void)service_.getStudentById(id);
        service_.updateStudent(inputStudentData(id));
        std::cout << "Student updated successfully.\n";
    } catch (const ApplicationException& exception) {
        std::cerr << exception.what() << '\n';
    }
}

void ConsoleUI::handleDeleteStudent() {
    try {
        service_.deleteStudent(readLine("Student ID: "));
        std::cout << "Student deleted successfully.\n";
    } catch (const ApplicationException& exception) {
        std::cerr << exception.what() << '\n';
    }
}

void ConsoleUI::run() {
    while (true) {
        if (!std::cin) return;
        displayMenu();
        const std::string input = readLine("Select an option: ");
        if (!std::cin) return;
        int option{};
        std::istringstream stream(input);
        char trailing{};
        if (!(stream >> option) || (stream >> trailing)) {
            std::cerr << "Invalid option.\n";
            continue;
        }
        switch (option) {
            case 1: handleAddStudent(); break;
            case 2: handleViewStudent(); break;
            case 3: handleListStudents(); break;
            case 4: handleUpdateStudent(); break;
            case 5: handleDeleteStudent(); break;
            case 0: return;
            default: std::cerr << "Invalid option.\n"; break;
        }
    }
}

} // namespace studentapp

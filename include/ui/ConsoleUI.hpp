#pragma once

#include "service/StudentService.hpp"

#include <iosfwd>
#include <string>

namespace studentapp {

class ConsoleUI {
public:
    explicit ConsoleUI(StudentService& service);
    void run();

private:
    void displayMenu() const;
    void handleAddStudent();
    void handleViewStudent();
    void handleListStudents();
    void handleUpdateStudent();
    void handleDeleteStudent();
    [[nodiscard]] Student inputStudentData(const std::string& studentId = {});
    [[nodiscard]] static std::string readLine(const std::string& prompt);
    [[nodiscard]] static std::uint16_t readYear();

    StudentService& service_;
};

} // namespace studentapp

#include "logging/ConsoleLogger.hpp"
#include "repository/StudentRepository.hpp"
#include "service/StudentService.hpp"
#include "ui/ConsoleUI.hpp"

#include <memory>

int main() {
    using namespace studentapp;
    auto repository = std::make_shared<StudentRepository>();
    auto logger = std::make_shared<ConsoleLogger>();
    StudentService service(repository, logger);
    ConsoleUI ui(service);
    ui.run();
    return 0;
}

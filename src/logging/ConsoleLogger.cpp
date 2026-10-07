#include "logging/ConsoleLogger.hpp"

#include <iostream>
#include <utility>

namespace studentapp {

void ConsoleLogger::logInfo(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "[INFO] " << message << '\n';
}

void ConsoleLogger::logWarning(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "[WARNING] " << message << '\n';
}

void ConsoleLogger::logError(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cerr << "[ERROR] " << message << '\n';
}

} // namespace studentapp

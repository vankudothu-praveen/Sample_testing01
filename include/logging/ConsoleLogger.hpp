#pragma once

#include "logging/ILogger.hpp"

#include <mutex>

namespace studentapp {

class ConsoleLogger final : public ILogger {
public:
    void logInfo(const std::string& message) override;
    void logWarning(const std::string& message) override;
    void logError(const std::string& message) override;

private:
    std::mutex mutex_;
};

} // namespace studentapp

#pragma once

#include <string>

namespace studentapp {

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void logInfo(const std::string& message) = 0;
    virtual void logWarning(const std::string& message) = 0;
    virtual void logError(const std::string& message) = 0;
};

} // namespace studentapp

// src/HermesLogger.cpp
#include "HermesLogger.h"

namespace Hermes {

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::dispatch(Level level, std::string_view message, 
                     const std::source_location& loc) {
    std::lock_guard lock(sinks_mutex);
    for (auto& sink : sinks) {
        sink->log(level, message, loc);
    }
}

} // namespace Hermes
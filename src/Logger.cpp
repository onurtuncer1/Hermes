#include "Logger.h"
#include <iostream>

namespace Hermes {

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::dispatch(Level level, std::string_view message,
                      const std::source_location& loc) {
    std::lock_guard lock(sinks_mutex);
    for (const auto& sink : sinks) {
        if (sink) {
            try {
                sink->log(level, message, loc);
            } catch (...) {
                std::cerr << "Logger sink threw an exception\n";
            }
        }
    }
}

} // namespace Hermes


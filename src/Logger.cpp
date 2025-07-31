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

void Logger::add_sink(std::shared_ptr<Sink> sink) {
    std::lock_guard lock(instance().sinks_mutex);
    instance().sinks.push_back(std::move(sink));
}

void Logger::set_level(Level level) {
    instance().current_level.store(level);
}

void Logger::clear_sinks_for_testing() {
    std::lock_guard lock(instance().sinks_mutex);
    instance().sinks.clear();
}

} // namespace Hermes


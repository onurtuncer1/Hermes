
#include "Logger.h"
#include <array>
#include <iostream>
#include <mutex>
#include <string_view>

namespace Hermes {

constexpr std::array<std::string_view, 6> level_names = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL"
};

void ConsoleSink::log(Logger::Level level, std::string_view message,
                     const std::source_location& loc) {
    static std::mutex cout_mutex;
    std::lock_guard lock(cout_mutex);
    
    std::cout << std::format("[{}] {} ({}:{})\n", 
        level_names[static_cast<int>(level)], 
        message, 
        loc.file_name(), 
        loc.line());
}

void ConsoleSink::flush() {
    std::cout << std::flush;
}

} // namespace Hermes
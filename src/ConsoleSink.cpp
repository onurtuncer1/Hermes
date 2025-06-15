

#include "HermesLogger.h"
#include <iostream>
#include <mutex>

namespace Hermes {

void ConsoleSink::log(Logger::Level level, std::string_view message,
                      const std::source_location& loc) {
    static std::mutex cout_mutex;
    std::lock_guard lock(cout_mutex);
    
    std::cout << std::format("[{}] {} ({}:{})\n", 
        magic_enum::enum_name(level), message, 
        loc.file_name(), loc.line());
}

void ConsoleSink::flush() {
    std::cout << std::flush;
}

} // namespace Hermes
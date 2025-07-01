#include "Logger.h"
#include <iostream>

namespace Hermes {

void ConsoleSink::log(Logger::Level level, std::string_view message,
                      const std::source_location& loc) {
    const char* level_names[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL" };
    std::cerr << "[" << level_names[static_cast<int>(level)] << "] "
              << message << " (" << loc.file_name() << ":" << loc.line() << ")\n";
}

void ConsoleSink::flush() {
    std::cerr << std::flush;
}

} // namespace Hermes

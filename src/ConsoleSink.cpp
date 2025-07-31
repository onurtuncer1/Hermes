#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>

namespace Hermes
{

namespace
{
const char *get_color(Logger::Level level)
{
	switch (level) {
	case Logger::Level::Trace:    return "\033[90m"; // Gray

	case Logger::Level::Debug:    return "\033[36m"; // Cyan

	case Logger::Level::Info:     return "\033[32m"; // Green

	case Logger::Level::Warn:     return "\033[33m"; // Yellow

	case Logger::Level::Error:    return "\033[31m"; // Red

	case Logger::Level::Critical: return "\033[1;31m"; // Bright Red

	default:                      return "\033[0m"; // Reset
	}
}

const char *get_level_name(Logger::Level level)
{
	switch (level) {
	case Logger::Level::Trace:    return "TRACE";

	case Logger::Level::Debug:    return "DEBUG";

	case Logger::Level::Info:     return "INFO";

	case Logger::Level::Warn:     return "WARN";

	case Logger::Level::Error:    return "ERROR";

	case Logger::Level::Critical: return "CRITICAL";

	default:                      return "UNKNOWN";
	}
}

std::string current_timestamp()
{
	using namespace std::chrono;
	auto now = system_clock::now();
	auto in_time_t = system_clock::to_time_t(now);
	auto millis = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

	std::ostringstream oss;
	oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S")
		<< '.' << std::setw(3) << std::setfill('0') << millis.count();
	return oss.str();
}
}


void ConsoleSink::log(Logger::Level level, std::string_view message,
					  const std::source_location &loc)
{
	const char *color = get_color(level);
	const char *reset = "\033[0m";

	std::cerr << color
			  << "[" << current_timestamp() << "] "
			  << "[" << get_level_name(level) << "] "
			  << message
			  << " (" << loc.file_name() << ":" << loc.line() << ")"
			  << reset << '\n';
}

void ConsoleSink::flush()
{
	std::cerr << std::flush;
}

} // namespace Hermes

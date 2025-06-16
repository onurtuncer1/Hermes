

#pragma once

#include <format>
#include <source_location>
#include <memory>
#include <vector>
#include <atomic>

namespace Hermes {

    
class Logger {
public:
    enum class Level { Trace, Debug, Info, Warn, Error, Critical, Off };

    // Interface for sinks (defined in header)
    class Sink {
    public:
        virtual ~Sink() = default;
        virtual void log(Level level, std::string_view message, 
                        const std::source_location& loc) = 0;
        virtual void flush() = 0;
    };

   template <typename... Args>
static void log(Level level, std::format_string<Args...> fmt, Args&&... args,
                const std::source_location& loc = std::source_location::current())
  {
        if (level < instance().current_level.load(std::memory_order_relaxed)) return;
        const auto formatted = std::format(fmt, std::forward<Args>(args)...);
        instance().dispatch(level, formatted, loc);
    }

    // Configuration (header-only)
    static void add_sink(std::unique_ptr<Sink> sink) {
        std::lock_guard lock(instance().sinks_mutex);
        instance().sinks.push_back(std::move(sink));
    }

    static void set_level(Level level) {
    instance().current_level.store(level);
}

private:
    // Singleton implementation
    static Logger& instance();

    // Implementation details (defined in .cpp when needed)
    void dispatch(Level level, std::string_view message, const std::source_location& loc);
    
    std::vector<std::unique_ptr<Sink>> sinks;
    std::mutex sinks_mutex;
    std::atomic<Level> current_level{Level::Info};
};

// Predefined sinks (declaration only)
class ConsoleSink : public Logger::Sink {
public:
    void log(Logger::Level level, std::string_view message, 
             const std::source_location& loc) override;
    void flush() override;
};

// Macro shortcuts (compile-time level filtering)
#define HERMES_TRACE(...)   Hermes::Logger::log(Hermes::Logger::Level::Trace, __VA_ARGS__)
#define HERMES_DEBUG(...)   Hermes::Logger::log(Hermes::Logger::Level::Debug, __VA_ARGS__)
#define HERMES_INFO(...)    Hermes::Logger::log(Hermes::Logger::Level::Info, __VA_ARGS__)
#define HERMES_WARN(...)    Hermes::Logger::log(Hermes::Logger::Level::Warn, __VA_ARGS__)
#define HERMES_ERROR(...)   Hermes::Logger::log(Hermes::Logger::Level::Error, __VA_ARGS__)
#define HERMES_CRITICAL(...) Hermes::Logger::log(Hermes::Logger::Level::Critical, __VA_ARGS__)

} // namespace Hermes


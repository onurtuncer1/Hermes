// Logger.h
#pragma once

#include <format>
#include <source_location>
#include <memory>
#include <vector>
#include <atomic>
#include <mutex>
#include <string_view>

namespace Hermes {

class Logger {
public:
    enum class Level { Trace, Debug, Info, Warn, Error, Critical, Off };

    class Sink {
    public:
        virtual ~Sink() = default;
        virtual void log(Level level, std::string_view message,
                         const std::source_location& loc) = 0;
        virtual void flush() = 0;
    };

    template <typename... Args>
    static void log(Level level, std::string_view fmt, Args&&... args) {
        log(std::source_location::current(), level, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void log(const std::source_location& loc,
                    Level level,
                    std::string_view fmt,
                    Args&&... args) {
        instance().log_with_location(loc, level, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void log_with_location(const std::source_location& loc,
                           Level level,
                           std::string_view fmt,
                           Args&&... args) {
        if (level < current_level.load(std::memory_order_relaxed)) return;
        const auto formatted = std::vformat(fmt, std::make_format_args(args...));
        dispatch(level, formatted, loc);
    }

    static void add_sink(std::shared_ptr<Sink> sink) {
        std::lock_guard lock(instance().sinks_mutex);
        instance().sinks.push_back(std::move(sink));
    }

    static void set_level(Level level) {
        instance().current_level.store(level);
    }

    static void clear_sinks_for_testing() {
        std::lock_guard lock(instance().sinks_mutex);
        instance().sinks.clear();
    }

private:
    Logger() = default;
    static Logger& instance();

    void dispatch(Level level, std::string_view message, const std::source_location& loc);

    std::vector<std::shared_ptr<Sink>> sinks;
    std::mutex sinks_mutex;
    std::atomic<Level> current_level{Level::Info};
};

class ConsoleSink : public Logger::Sink {
public:
    void log(Logger::Level level, std::string_view message,
             const std::source_location& loc) override;
    void flush() override;
};

// #define HERMES_TRACE(...)    Hermes::Logger::log(Hermes::Logger::Level::Trace, __VA_ARGS__)
// #define HERMES_DEBUG(...)    Hermes::Logger::log(Hermes::Logger::Level::Debug, __VA_ARGS__)
// #define HERMES_INFO(...)     Hermes::Logger::log(Hermes::Logger::Level::Info, __VA_ARGS__)
// #define HERMES_WARN(...)     Hermes::Logger::log(Hermes::Logger::Level::Warn, __VA_ARGS__)
// #define HERMES_ERROR(...)    Hermes::Logger::log(Hermes::Logger::Level::Error, __VA_ARGS__)
// #define HERMES_CRITICAL(...) Hermes::Logger::log(Hermes::Logger::Level::Critical, __VA_ARGS__)

} // namespace Hermes
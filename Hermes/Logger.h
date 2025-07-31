/// @file Logger.h
/// @brief Lightweight logging framework for the Hermes project.

#pragma once

#include <format>
#include <source_location>
#include <memory>
#include <vector>
#include <atomic>
#include <mutex>
#include <string_view>

namespace Hermes {

/**
 * @brief Logger class providing static logging methods and log level management.
 *
 * Supports multiple log sinks and includes support for capturing source location information.
 */
class Logger {
public:
    /**
     * @brief Logging levels.
     */
    enum class Level {
        Trace,     ///< Verbose debugging information.
        Debug,     ///< General debugging information.
        Info,      ///< Informational messages.
        Warn,      ///< Warnings that don’t interrupt execution.
        Error,     ///< Errors that allow the program to continue.
        Critical,  ///< Severe errors likely leading to termination.
        Off        ///< Logging disabled.
    };

    /**
     * @brief Abstract base class for all logging sinks.
     */
    class Sink {
    public:
        /// Virtual destructor.
        virtual ~Sink() = default;

        /**
         * @brief Logs a formatted message at a specific level.
         *
         * @param level The log level.
         * @param message The message to log.
         * @param loc Source location of the log call.
         */
        virtual void log(Level level,
                         std::string_view message,
                         const std::source_location& loc) = 0;

        /// @brief Flush any buffered log output.
        virtual void flush() = 0;
    };

    /**
     * @brief Logs a message at the given level with formatting.
     *
     * Uses `std::source_location::current()` to capture the call site.
     *
     * @tparam Args Variadic arguments for formatting.
     * @param level The logging level.
     * @param fmt Format string.
     * @param args Format arguments.
     */
    template <typename... Args>
    static void log(Level level, std::string_view fmt, Args&&... args);

    /**
     * @brief Logs a message with an explicitly provided source location.
     *
     * @tparam Args Variadic arguments for formatting.
     * @param loc Source location.
     * @param level Logging level.
     * @param fmt Format string.
     * @param args Format arguments.
     */
    template <typename... Args>
    static void log(const std::source_location& loc,
                    Level level,
                    std::string_view fmt,
                    Args&&... args);

    /**
     * @brief Instance method to log with explicit source location.
     *
     * @tparam Args Variadic arguments for formatting.
     * @param loc Source location.
     * @param level Logging level.
     * @param fmt Format string.
     * @param args Format arguments.
     */
    template <typename... Args>
    void log_with_location(const std::source_location& loc,
                           Level level,
                           std::string_view fmt,
                           Args&&... args);

    /**
     * @brief Adds a sink to the global logger instance.
     *
     * @param sink Shared pointer to a Sink implementation.
     */
    static void add_sink(std::shared_ptr<Sink> sink);

    /**
     * @brief Sets the global log level threshold.
     *
     * Messages below this level will be ignored.
     *
     * @param level Logging level to set.
     */
    static void set_level(Level level);

    /**
     * @brief Removes all logging sinks. Used primarily for testing.
     */
    static void clear_sinks_for_testing();

private:
    /// Private constructor for singleton pattern.
    Logger() = default;

    /**
     * @brief Returns the singleton logger instance.
     * @return Reference to the singleton logger.
     */
    static Logger& instance();

    /**
     * @brief Dispatches a formatted message to all registered sinks.
     *
     * @param level Logging level.
     * @param message The formatted message.
     * @param loc Source location.
     */
    void dispatch(Level level, std::string_view message, const std::source_location& loc);

    std::vector<std::shared_ptr<Sink>> sinks; ///< Registered sinks.
    std::mutex sinks_mutex; ///< Mutex for sink access.
    std::atomic<Level> current_level{Level::Info}; ///< Current logging level.
};

/**
 * @brief A simple sink that writes log messages to the console.
 */
class ConsoleSink : public Logger::Sink {
public:
    /**
     * @brief Logs a message to the console.
     *
     * @param level Logging level.
     * @param message The message to log.
     * @param loc Source location.
     */
    void log(Logger::Level level,
             std::string_view message,
             const std::source_location& loc) override;

    /// @brief Flushes the console output.
    void flush() override;
};

} // namespace Hermes

// // #define HERMES_TRACE(...)    Hermes::Logger::log(Hermes::Logger::Level::Trace, __VA_ARGS__)
// // #define HERMES_DEBUG(...)    Hermes::Logger::log(Hermes::Logger::Level::Debug, __VA_ARGS__)
// // #define HERMES_INFO(...)     Hermes::Logger::log(Hermes::Logger::Level::Info, __VA_ARGS__)
// // #define HERMES_WARN(...)     Hermes::Logger::log(Hermes::Logger::Level::Warn, __VA_ARGS__)
// // #define HERMES_ERROR(...)    Hermes::Logger::log(Hermes::Logger::Level::Error, __VA_ARGS__)
// // #define HERMES_CRITICAL(...) Hermes::Logger::log(Hermes::Logger::Level::Critical, __VA_ARGS__)


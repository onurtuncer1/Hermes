#include <Logger.h>
#include <catch2/catch_test_macros.hpp>
#include <sstream>

class TestSink : public Hermes::Logger::Sink {
public:
    std::ostringstream stream;

    void log(Hermes::Logger::Level level, std::string_view message,
             const std::source_location& loc) override {
        const char* level_names[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL"};
        stream << "[" << level_names[static_cast<int>(level)] << "] "
               << message << "\n";
    }

    void flush() override {}
};

TEST_CASE("Sink system", "[sinks]") {
    auto shared_sink = std::make_shared<TestSink>();
    Hermes::Logger::clear_sinks_for_testing();  
    Hermes::Logger::set_level(Hermes::Logger::Level::Trace);

    SECTION("Messages reach sinks") {
        Hermes::Logger::log(Hermes::Logger::Level::Error, "Test error");
        REQUIRE(shared_sink->stream.str().find("[ERROR] Test error") != std::string::npos);
    }
}



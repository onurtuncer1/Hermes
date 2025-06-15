#include <HermesLogger.h>
#include <catch2/catch_test_macros.hpp>
#include <sstream>

class TestSink : public Hermes::Logger::Sink {
public:
    std::ostringstream stream;

    void log(Hermes::Logger::Level level, std::string_view message,
             const std::source_location& loc) override {
        stream << "[" << magic_enum::enum_name(level) << "] "
               << message << "\n";
    }

    void flush() override {}
};

TEST_CASE("Sink system", "[sinks]") {
    auto test_sink = std::make_unique<TestSink>();
    auto& sink_ref = *test_sink;
    
    Hermes::Logger::add_sink(std::move(test_sink));
    Hermes::Logger::set_level(Hermes::Logger::Level::Trace);

    SECTION("Messages reach sinks") {
        Hermes::Logger::log(Hermes::Logger::Level::Error, "Test error");
        REQUIRE(sink_ref.stream.str().find("[ERROR] Test error") != std::string::npos);
    }

    SECTION("Level filtering at sink level") {
        Hermes::Logger::log(Hermes::Logger::Level::Debug, "Debug message");
        REQUIRE(sink_ref.stream.str().find("Debug message") != std::string::npos);
    }
}
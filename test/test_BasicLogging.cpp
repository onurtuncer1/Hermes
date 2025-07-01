#include <Logger.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Basic logging functionality", "[core]") {
    Hermes::Logger::clear_sinks_for_testing();
    Hermes::Logger::set_level(Hermes::Logger::Level::Info);
    Hermes::Logger::add_sink(std::make_shared<Hermes::ConsoleSink>());

    SECTION("Formatting works") {
        Hermes::Logger::log(Hermes::Logger::Level::Info, "Value: {}", 42);
        REQUIRE(true);
    }
}

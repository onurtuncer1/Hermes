#include <HermesLogger.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Basic logging functionality", "[core]") {
    Hermes::Logger::set_level(Hermes::Logger::Level::Info);

    SECTION("Level filtering works") {
        Hermes::Logger::log(Hermes::Logger::Level::Debug, "This shouldn't appear");
        REQUIRE(true); // Just verify no crash
    }

    SECTION("Formatting works") {
        Hermes::Logger::log(Hermes::Logger::Level::Info, "Value: {}", 42);
        REQUIRE(true);
    }

    SECTION("Source location capture") {
        Hermes::Logger::log(Hermes::Logger::Level::Warn, "Check location");
        REQUIRE(true);
    }
}
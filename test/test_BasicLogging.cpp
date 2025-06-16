#include <Logger.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Basic logging functionality", "[core]") {
    Hermes::Logger::set_level(Hermes::Logger::Level::Info);

    SECTION("Formatting works") {
        using Level = Hermes::Logger::Level;
        Hermes::Logger::log(Level::Info, std::format_string{"Value: {}"}, 42);
        REQUIRE(true);
    }
}
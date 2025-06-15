#include <HermesLogger.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("CAD convenience macros", "[macros]") {
    #define HERMES_LOG_GEOM(fmt, ...) \
        Hermes::Logger::log(Hermes::Logger::Level::Info, "[GEOM] " fmt, ##__VA_ARGS__)

    SECTION("Geometry macro works") {
        HERMES_LOG_GEOM("Surface area: {:.3f}", 123.456789);
        REQUIRE(true); // Verify compilation
    }
}
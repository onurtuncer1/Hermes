// ----------------------------------------------------------------------
// Project: Hermes Logging Library
// Copyright(c) 2025 Onur Tuncer, PhD, Istanbul Technical University
//
// SPDX - License - Identifier : MIT
// License - Filename : LICENSE
// ----------------------------------------------------------------------

#include <Hermes/Logger.h>
#include <catch2/catch.hpp> 

using namespace Hermes;

TEST_CASE("Basic logging functionality", "[core]")
{
	Logger::clear_sinks_for_testing();
	Logger::set_level(Hermes::Logger::Level::Info);
	Logger::add_sink(std::make_shared<Hermes::ConsoleSink>());

	SECTION("Formatting works") {
		Logger::log(Hermes::Logger::Level::Info, "Value: {}", 42);
		Logger::log(Hermes::Logger::Level::Warn, "Value: {}", 43);
		REQUIRE(true);
	}
}

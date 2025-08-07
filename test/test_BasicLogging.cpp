// ----------------------------------------------------------------------
// Project: Hermes Logging Library
// Copyright(c) 2025 Onur Tuncer, PhD, Istanbul Technical University
//
// SPDX - License - Identifier : MIT
// License - Filename : LICENSE
// ----------------------------------------------------------------------

#include <catch2/catch_test_macros.hpp>
#include <Hermes/Logger.h>

using namespace Hermes;

TEST_CASE("Basic logging functionality", "[core]")
{
	Logger::clear_sinks();
	Logger::set_level(Hermes::Logger::Level::Trace);
	Logger::set_level(Hermes::Logger::Level::Debug);
	Logger::set_level(Hermes::Logger::Level::Warn);
	Logger::set_level(Hermes::Logger::Level::Error);
	Logger::set_level(Hermes::Logger::Level::Critical);
	Logger::set_level(Hermes::Logger::Level::Info);

	auto test_sink = std::make_shared<Hermes::ConsoleSink>();
	Logger::add_sink(test_sink);

	SECTION("Formatting works") {
		Logger::log(Hermes::Logger::Level::Trace, "Value: {}", 40);
		Logger::log(Hermes::Logger::Level::Debug, "Value: {}", 41);
		Logger::log(Hermes::Logger::Level::Info, "Value: {}", 42);
		Logger::log(Hermes::Logger::Level::Warn, "Value: {}", 43);
		Logger::log(Hermes::Logger::Level::Error, "Value: {}", 44);
		Logger::log(Hermes::Logger::Level::Critical, "Value: {}", 45);
		REQUIRE(true);
	}

	test_sink->flush();
}

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

	auto test_sink = std::make_shared<Hermes::ConsoleSink>();
	Logger::add_sink(test_sink);

	SECTION("Formatting works") {
		using Level = Hermes::Logger::Level;
		HLOG(Level::Trace, "Value: {}", 40);
		HLOG(Level::Debug, "Value: {}", 41);
		HLOG(Level::Info, "Value: {}", 42);
		HLOG(Level::Warn, "Value: {}", 43);
		HLOG(Level::Error, "Value: {}", 44);
		HLOG(Level::Critical, "Value: {}", 45);
		REQUIRE(true);
	}

	test_sink->flush();
}
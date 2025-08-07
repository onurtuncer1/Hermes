// ----------------------------------------------------------------------
// Project: Hermes Logging Library
// Copyright(c) 2025 Onur Tuncer, PhD, Istanbul Technical University
//
// SPDX - License - Identifier : MIT
// License - Filename : LICENSE
// ----------------------------------------------------------------------

#include <sstream>
#include <catch2/catch_test_macros.hpp>
#include <Hermes/Logger.h>

struct Point3D { double x, y, z; };

template <>
struct std::formatter<Point3D> {
	auto parse(format_parse_context &ctx)
	{
		return ctx.begin();
	}

	auto format(const Point3D &p, format_context &ctx) const
	{
		return format_to(ctx.out(), "({:.2f}, {:.2f}, {:.2f})", p.x, p.y, p.z);
	}
};

TEST_CASE("CAD geometry logging", "[cad]")
{
	auto test_sink = std::make_unique<TestSink>();
	auto &sink_ref = *test_sink;
	Hermes::Logger::add_sink(std::move(test_sink)));

	SECTION("3D point formatting") {
		Point3D p{1.23456, 2.34567, 3.45678};
		Hermes::Logger::log(Hermes::Logger::Level::Info, "Point: {}", p);

		REQUIRE(sink_ref.stream.str().find("(1.23, 2.35, 3.46)") != std::string::npos);
	}


}
#include <catch2/catch_test_macros.hpp>
#include <Hermes/Logger.h>
#include <sstream>
#include <iostream>

class ThrowingSink : public Hermes::Logger::Sink {
public:
	void log(Hermes::Logger::Level,
	         std::string_view,
	         const std::source_location&) override
	{
		throw std::runtime_error("Oops from sink");
	}

	void flush() override {}
};


using namespace Hermes;

TEST_CASE("Logger dispatch handles exceptions from sink", "[logger][exception]") {
	// Prepare a throwing sink
	auto bad_sink = std::make_shared<ThrowingSink>();

	// Redirect std::cerr to a stringstream
	std::stringstream captured_cerr;
	auto* old_buf = std::cerr.rdbuf();  // save original buffer
	std::cerr.rdbuf(captured_cerr.rdbuf());

	Logger::clear_sinks();
	Logger::add_sink(bad_sink);
	Logger::set_level(Logger::Level::Trace); // ensure the message passes level check

	// Perform the log call
	Logger::log(std::source_location::current(), Logger::Level::Error, "This will cause sink to throw");

	// Restore std::cerr
	std::cerr.rdbuf(old_buf);

	// Check that the error message was printed
	const std::string output = captured_cerr.str();
	REQUIRE(output.find("Logger sink threw an exception") != std::string::npos);
}

cmake_minimum_required(VERSION 3.21)

# Find Catch2 (v3+ recommended)
find_package(Catch2 REQUIRED)

# Test executable
add_executable(HermesLoggerTests
  TestBasicLogging.cpp
  TestSinks.cpp
  TestCADFormatters.cpp
)

target_link_libraries(HermesLoggerTests PRIVATE
  Hermes::Logger
  Catch2::Catch2WithMain
)

# Enable test discovery
catch_discover_tests(HermesLoggerTests)
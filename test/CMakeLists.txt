cmake_minimum_required(VERSION 3.21)

project(HermesLoggerTests LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.4
)
FetchContent_MakeAvailable(Catch2)

include(Catch)

add_executable(HermesLoggerTests
  test_BasicLogging.cpp
  # test_Sinks.cpp
  # test_Formatters.cpp
  # test_Macros.cpp
)

target_link_libraries(HermesLoggerTests PRIVATE
  Hermes::Logger
  Catch2::Catch2WithMain
)


catch_discover_tests(HermesLoggerTests)



include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.4
)
FetchContent_MakeAvailable(Catch2)

include(Catch)

add_executable(${PROJECT_NAME}Tests
  test_BasicLogging.cpp
  test_Sinks.cpp
  # test_Formatters.cpp
)

target_link_libraries(${PROJECT_NAME}Tests PRIVATE
  ${PROJECT_NAME}::Logger
  Catch2::Catch2WithMain
)


catch_discover_tests(${PROJECT_NAME}Tests)


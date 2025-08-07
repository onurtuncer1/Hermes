# ------------------------------------------------------------------------------
# Project: Hermes Logging Library
# Copyright (c) 2025, Onur Tuncer, PhD, Istanbul Technical University
#
# SPDX-License-Identifier: MIT
# License-Filename: LICENSE
# ------------------------------------------------------------------------------

find_package(Catch2 REQUIRED)

add_executable(${PROJECT_NAME}Tests
  test_BasicLogging.cpp
  test_Sinks.cpp
  test_Exception.cpp
  test_Formatters.cpp
)

target_link_libraries(${PROJECT_NAME}Tests PRIVATE
  ${PROJECT_NAME}::Logger
  Catch2::Catch2WithMain
)

enable_testing()
add_test(NAME ${PROJECT_NAME}Tests COMMAND ${PROJECT_NAME}Tests)


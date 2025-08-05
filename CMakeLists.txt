# ------------------------------------------------------------------------------
# Project: Hermes Logging Library
# Copyright (c) 2025, Onur Tuncer, PhD, Istanbul Technical University
#
# SPDX-License-Identifier: MIT
# License-Filename: LICENSE
# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.22)

project(Hermes
  VERSION 1.0.0
  LANGUAGES CXX
  DESCRIPTION "High performance logging"
)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_library(${PROJECT_NAME})
add_library(Hermes::Logger ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${PROJECT_NAME}>
)

target_sources(${PROJECT_NAME} PRIVATE
  src/Logger.cpp
  src/ConsoleSink.cpp
  # src/sinks/FileSink.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# include(GNUInstallDirs)
# install(TARGETS Hermes
#   EXPORT HermesLoggerTargets
#   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(EXPORT HermesLoggerTargets
#   FILE HermesLoggerConfig.cmake
#   NAMESPACE Hermes::
#   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
# )

if (BUILD_DOCS)
  add_subdirectory(doc)
endif()

if (ENABLE_STATIC_ANALYSIS)
  include(cppcheck)
endif()

if(BUILD_TESTS)
	include(coverage)
	add_coverage_target("*/vendor/*") # exclude from coverage
	enable_testing()
	add_subdirectory(test)
endif()

if(CMAKE_BUILD_TYPE MATCHES "AddressSanitizer")
  include(sanitizers)
elseif(CMAKE_BUILD_TYPE MATCHES "MemorySanitizer")
  include(sanitizers)
elseif(CMAKE_BUILD_TYPE MATCHES "ThreadSanitizer")
  include(sanitizers)
elseif(CMAKE_BUILD_TYPE MATCHES "UndefinedBehaviorSanitizer")
  include(sanitizers)
endif()

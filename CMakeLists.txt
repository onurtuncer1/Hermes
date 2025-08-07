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

if (BUILD_DOCS)
  add_subdirectory(doc)
endif()

if (ENABLE_STATIC_ANALYSIS)
  include(cppcheck)
endif()

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()

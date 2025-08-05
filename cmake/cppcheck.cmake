# ------------------------------------------------------------------------------
# Copyright (c) 2025 Onur Tuncer, PhD, Istanbul Technical University
#
# SPDX-License-Identifier: MIT
# License-Filename: LICENSE
# ------------------------------------------------------------------------------

# Check prerequisites
FIND_PROGRAM(CPPCHECK_PATH cppcheck)

IF(NOT CPPCHECK_PATH)
    MESSAGE(FATAL_ERROR "cppcheck not found! Aborting...")
ENDIF()

# Gather source files
file(GLOB_RECURSE APP_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Set directories for analysis
set(STATIC_ANALYSIS_SOURCE_DIR ${CMAKE_SOURCE_DIR})  # Updated to CMAKE_SOURCE_DIR
set(STATIC_ANALYSIS_REPORT_DIR ${CMAKE_BINARY_DIR}/static_analysis)
file(MAKE_DIRECTORY ${STATIC_ANALYSIS_REPORT_DIR})
set(STATIC_ANALYSIS_XML_FILE ${STATIC_ANALYSIS_REPORT_DIR}/static_analysis_report.xml)

# Add namespaced custom target for static analysis (using CMake project name)
set(NAMESPACED_TARGET "static_analysis")
add_custom_target(${NAMESPACED_TARGET})

# Add custom command to run cppcheck and generate the report
add_custom_command(TARGET ${NAMESPACED_TARGET}
  COMMAND cppcheck
   ARGS  --enable=all
         --force
         --suppress=unusedFunction
         --cppcheck-build-dir=${STATIC_ANALYSIS_REPORT_DIR}
         -I/${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}
         --suppressions-list=${CMAKE_BINARY_DIR}/../../tools/cppcheck/CppCheckSuppressions.txt
         --inconclusive
         --xml-version=2
         -v ${APP_SOURCES}
         --output-file=${STATIC_ANALYSIS_XML_FILE}
  COMMAND cppcheck-htmlreport
    ARGS    --title=${CMAKE_PROJECT_NAME}
            --file=${STATIC_ANALYSIS_XML_FILE}
            --report-dir=${STATIC_ANALYSIS_REPORT_DIR}
            --source-dir=${STATIC_ANALYSIS_SOURCE_DIR}
            --source-encoding=UTF-8  # Changed to UTF-8
    DEPENDS ${STATIC_ANALYSIS_XML_FILE}
  COMMENT "Running static analysis tool & generating html report"
  VERBATIM)


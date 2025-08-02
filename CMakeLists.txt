cmake_minimum_required(VERSION 3.28)

project(Hermes
  VERSION 1.0.0
  LANGUAGES CXX
  DESCRIPTION "High performance logging"
)

add_library(${PROJECT_NAME})
add_library(Hermes::Logger ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}>
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
# install(TARGETS HermesLogger
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
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  add_subdirectory(doc)
endif()

if(BUILD_TESTS)
	set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
	include(coverage)
	add_coverage_target("*/vendor/*") # exclude from coverage
	enable_testing()
	add_subdirectory(test)
endif()

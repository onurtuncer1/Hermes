cmake_minimum_required(VERSION 3.21)
project(HermesLogger
  VERSION 1.0.0
  LANGUAGES CXX
  DESCRIPTION "CAD-optimized logging"
)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(HermesLogger)
add_library(Hermes::Logger ALIAS HermesLogger)

# Public API headers
target_include_directories(HermesLogger
  PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


target_sources(HermesLogger PRIVATE
  src/LoggerCore.cpp
  src/sinks/ConsoleSink.cpp
  src/sinks/FileSink.cpp
)


option(HERMES_ENABLE_GEOMETRY_LOGGING "Specialized CAD formatters" ON)
option(HERMES_ENABLE_SIMD "Vectorized formatting" OFF) # Controlled via presets

if(HERMES_ENABLE_GEOMETRY_LOGGING)
  target_sources(HermesLogger PRIVATE
    src/formatters/GeometryFormatters.cpp
    src/formatters/BRepFormatters.cpp
  )
  target_compile_definitions(HermesLogger PRIVATE HERMES_HAS_GEOMETRY_FORMATTERS=1)
endif()


find_package(Threads REQUIRED)
target_link_libraries(HermesLogger PRIVATE Threads::Threads)

# SIMD (configured via presets)
if(HERMES_ENABLE_SIMD)
  find_package(Vc 1.4 REQUIRED)
  target_link_libraries(HermesLogger PRIVATE Vc::Vc)
endif()


include(GNUInstallDirs)
install(TARGETS HermesLogger
  EXPORT HermesLoggerTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT HermesLoggerTargets
  FILE HermesLoggerConfig.cmake
  NAMESPACE Hermes::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HermesLogger
)


if(HERMES_BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
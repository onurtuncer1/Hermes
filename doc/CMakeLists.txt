
cmake_minimum_required(VERSION 3.28)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED)


# Namespace the variables to avoid conflict
set(PROJECT_DOC_NAME "Hermes_${CMAKE_CURRENT_PROJECT_NAME}_Docs")

# Find all the public headers
get_target_property(PROJECT_PUBLIC_HEADER_DIR Hermes INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE PROJECT_PUBLIC_HEADERS ${PROJECT_PUBLIC_HEADER_DIR}/*.h)

set(${PROJECT_DOC_NAME}_DOXYGEN_INPUT_DIR  ${PROJECT_SOURCE_DIR}/src)
set(${PROJECT_DOC_NAME}_DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(${PROJECT_DOC_NAME}_DOXYGEN_INDEX_FILE ${${PROJECT_DOC_NAME}_DOXYGEN_OUTPUT_DIR}/xml/index.xml)
set(${PROJECT_DOC_NAME}_DOXYFILE_IN        ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(${PROJECT_DOC_NAME}_DOXYFILE_OUT       ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Set the Doxygen input and output directories in the Doxyfile
configure_file(${${PROJECT_DOC_NAME}_DOXYFILE_IN} ${${PROJECT_DOC_NAME}_DOXYFILE_OUT} @ONLY)

# Doxygen won't create this for us
file(MAKE_DIRECTORY ${${PROJECT_DOC_NAME}_DOXYGEN_OUTPUT_DIR})

# Only regenerate Doxygen when the Doxyfile or public headers change
add_custom_command(OUTPUT ${${PROJECT_DOC_NAME}_DOXYGEN_INDEX_FILE}
    DEPENDS ${PROJECT_PUBLIC_HEADERS}
    COMMAND ${DOXYGEN_EXECUTABLE} ${${PROJECT_DOC_NAME}_DOXYFILE_OUT}
    MAIN_DEPENDENCY ${${PROJECT_DOC_NAME}_DOXYFILE_OUT} ${${PROJECT_DOC_NAME}_DOXYFILE_IN}
    COMMENT "Generating ${PROJECT_DOC_NAME} docs"
    VERBATIM)

# Nice named target so we can run the job easily
add_custom_target(${PROJECT_DOC_NAME}_Doxygen ALL DEPENDS ${${PROJECT_DOC_NAME}_DOXYGEN_INDEX_FILE})

# Namespace Sphinx variables
set(${PROJECT_DOC_NAME}_SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(${PROJECT_DOC_NAME}_SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
set(${PROJECT_DOC_NAME}_SPHINX_INDEX_FILE ${${PROJECT_DOC_NAME}_SPHINX_BUILD}/index.html)

# Only regenerate Sphinx when:
#  - Doxygen has rerun
#  - Our doc files have been updated
#  - The Sphinx config has been updated
add_custom_command(OUTPUT ${${PROJECT_DOC_NAME}_SPHINX_INDEX_FILE}
    COMMAND ${SPHINX_EXECUTABLE} -b html
        -Dbreathe_projects.${CMAKE_PROJECT_NAME}=${${PROJECT_DOC_NAME}_DOXYGEN_OUTPUT_DIR}/xml
        ${${PROJECT_DOC_NAME}_SPHINX_SOURCE} ${${PROJECT_DOC_NAME}_SPHINX_BUILD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/index.rst ${${PROJECT_DOC_NAME}_DOXYGEN_INDEX_FILE}
    MAIN_DEPENDENCY ${${PROJECT_DOC_NAME}_SPHINX_SOURCE}/conf.py
    COMMENT "Generating ${PROJECT_DOC_NAME} documentation with Sphinx")

# Nice named target so we can run the job easily
add_custom_target(${PROJECT_DOC_NAME}_Sphinx ALL DEPENDS ${${PROJECT_DOC_NAME}_SPHINX_INDEX_FILE})

include(GNUInstallDirs)
install(DIRECTORY ${${PROJECT_DOC_NAME}_SPHINX_BUILD}
    DESTINATION ${CMAKE_INSTALL_DOCDIR})

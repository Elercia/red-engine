cmake_minimum_required(VERSION 3.12)

# Hunter dependencies
include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.249.tar.gz"
        SHA1 "d45d77d8bba9da13e9290a180e0477e90accd89b"
)

project(red-engine
        VERSION 0.0
        DESCRIPTION "2D Game engine"
        LANGUAGES CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Have cmake create a compile database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(${PROJECT_NAME}_BASE_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/output)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/lib)
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/lib)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/bin)
set(CMAKE_INSTALL_PREFIX ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/install)

# Hunter libs
include(cmake/HunterLibs.cmake)

# Build Utils
include(cmake/BuildUtils.cmake)

# Project options
include(cmake/ProjectOptions.cmake)

# Legacy External dependencies
add_subdirectory(external)

# Engine main directory
add_subdirectory(engine)

# Engine templates directory
option(RED_BUILD_TEMPLATES "Enable compilation of templates" ON)
if (RED_BUILD_TEMPLATES)
    message(STATUS "Building templates")
    add_subdirectory(templates)
endif ()

## Engine tests
option(RED_ENABLE_TESTING "Enable Test Builds" ON)
if (RED_ENABLE_TESTING)
    message(STATUS "Building tests")
    enable_testing()
    add_subdirectory(test)
endif ()
cmake_minimum_required(VERSION 3.12)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.249.tar.gz"
        SHA1 "d45d77d8bba9da13e9290a180e0477e90accd89b"
)

project(red-engine
        VERSION 0.0
        DESCRIPTION "Sample game-engine to try-out my skills"
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Have cmake create a compile database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(${PROJECT_NAME}_BASE_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/output)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/bin)

#Hunter dependencies
include(cmake/HunterLibs.cmake)

#Legacy External dependencies
add_subdirectory(external)

# Engine main directory
add_subdirectory(engine)

# Engine templates directory
add_subdirectory(templates)

## Engine tests
add_subdirectory(test)
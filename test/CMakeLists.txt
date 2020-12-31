cmake_minimum_required(VERSION 3.18)

project(red_engine_test
        VERSION 0.0
        DESCRIPTION ""
        LANGUAGES CXX C)

enable_testing()

# Source files
file(GLOB_RECURSE SOURCES
        src/*.cpp
        )

# Headers files
file(GLOB_RECURSE HEADERS
        include/*.hpp
        )

# Natvis files
file(GLOB_RECURSE NATVIS_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../Docs/natvis/*.natvis
        )

add_executable(red_engine_test ${SOURCES} ${HEADERS} ${NATVIS_FILES})

target_link_libraries(red_engine_test PRIVATE Catch2::Catch2 red_engine_lib)
target_include_directories(red_engine_test PRIVATE "include")

set_property(TARGET red_engine_test PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}  )

include(CTest)
include(Catch)
include(ParseAndAddCatchTests)
catch_discover_tests(red_engine_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# IDE Integration
set_property(TARGET red_engine_test PROPERTY FOLDER "test")
set(root ${CMAKE_CURRENT_SOURCE_DIR})

source_group(TREE ${root} FILES ${SOURCES})
source_group(TREE ${root} FILES ${HEADERS})
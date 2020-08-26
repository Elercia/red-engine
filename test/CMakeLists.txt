cmake_minimum_required(VERSION 3.12)

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

set_target_properties(red_engine_test
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/tests/"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/tests/"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/"
        )

add_custom_command(TARGET red_engine_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:red_engine_test>/resources)

red_add_optick(red_engine_test)

include(CTest)
include(Catch)
include(ParseAndAddCatchTests)
catch_discover_tests(red_engine_test WORKING_DIRECTORY $<TARGET_FILE_DIR:red_engine_test>)
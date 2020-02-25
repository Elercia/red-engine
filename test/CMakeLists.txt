cmake_minimum_required(VERSION 3.12)

project(red_engine_test
        VERSION 0.0
        DESCRIPTION ""
        LANGUAGES CXX C)

enable_testing()

set(SOURCES src/main.cpp
            src/ecs.cpp)

add_executable(red_engine_test ${SOURCES})

target_link_libraries(red_engine_test PRIVATE Catch2::Catch2 red_engine_lib)

include(CTest)
include(Catch)
catch_discover_tests(red_engine_test)
cmake_minimum_required(VERSION 3.12)

project(red_engine_test
        VERSION 0.0
        DESCRIPTION ""
        LANGUAGES CXX C)

enable_testing()

set(SOURCES src/main.cpp
        src/world_test.cpp
        src/system_test.cpp)

set(HEADERS include/system_test.hpp)

add_executable(red_engine_test ${SOURCES} ${HEADERS})

target_link_libraries(red_engine_test PRIVATE Catch2::Catch2 red_engine_lib)
target_include_directories(red_engine_test PRIVATE "include")


include(CTest)
include(Catch)
catch_discover_tests(red_engine_test)
cmake_minimum_required(VERSION 3.18)

set(SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INCLUDE_FOLDER_INTERN ${INCLUDE_FOLDER}/RedEngine)

# Source files
file(GLOB_RECURSE SOURCES
        ${SOURCE_FOLDER}/*.cpp
        )

# Headers files
file(GLOB_RECURSE HEADERS
        ${INCLUDE_FOLDER_INTERN}/*.hpp
        )

# Headers files
file(GLOB_RECURSE INLINE_HEADERS
        ${INCLUDE_FOLDER_INTERN}/*.inl
        )

# red_engine_lib
add_library(red_engine_lib STATIC ${SOURCES} ${HEADERS} ${INLINE_HEADERS})

target_include_directories(red_engine_lib
        PUBLIC
        ${INCLUDE_FOLDER})

# SDL2
target_link_libraries(red_engine_lib PUBLIC
        SDL2::SDL2
        SDL2::SDL2main
        SDL_image::SDL_image)

# FMT
target_link_libraries(red_engine_lib PUBLIC
        fmt::fmt)

# Debug Break
target_link_libraries(red_engine_lib PUBLIC
        debug_break)

# Json nlohmann_json
target_link_libraries(red_engine_lib PUBLIC
    nlohmann_json::nlohmann_json)

# Box2D 
target_link_libraries(red_engine_lib PUBLIC
    Box2D::Box2D)

# Fmod
target_link_libraries(red_engine_lib PUBLIC
        FmodStudio FmodCore)

get_target_property(prop FmodCore INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS ${prop})

# Profiler Optick
option(RED_USE_PROFILER "Enable game profiler" ON)

message(STATUS "Use red-engine profiler : ${RED_USE_PROFILER}")
if (RED_USE_PROFILER)
    # Optick Profiler
    target_link_libraries(red_engine_lib
        PUBLIC
        OptickCore)

    target_compile_definitions(red_engine_lib
        PUBLIC
        RED_USE_PROFILER)
endif ()

red_set_compile_definition(red_engine_lib)

# IDE Integration
set_property(TARGET red_engine_lib PROPERTY FOLDER "engine")
set(root ${CMAKE_CURRENT_SOURCE_DIR})

source_group(TREE ${root} FILES ${SOURCES})
source_group(TREE ${root} FILES ${HEADERS})
source_group(TREE ${root} FILES ${INLINE_HEADERS})
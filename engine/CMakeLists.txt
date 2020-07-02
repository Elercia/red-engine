cmake_minimum_required(VERSION 3.12)

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
add_library(red_engine_lib STATIC ${SOURCES} ${HEADERS} ${INLINE_HEADERS} "include/RedEngine/Resources/AnnimationDescriptor.hpp")

target_include_directories(red_engine_lib
        PUBLIC
        ${INCLUDE_FOLDER})


# SLD2
target_link_libraries(red_engine_lib
        PUBLIC
        SDL2::SDL2
        SDL2::SDL2main
        SDL_image::SDL_image)

# FMT
target_link_libraries(red_engine_lib
        PUBLIC
        fmt::fmt)

# Debug Break
target_link_libraries(red_engine_lib
        PUBLIC
        debug_break)

# Json nlohmann_json
target_link_libraries(red_engine_lib 
    PUBLIC 
    nlohmann_json::nlohmann_json)

option(RED_USE_PROFILER "Enable application profiler usage" ON)

if (MINGW OR UNIX)
    set(RED_USE_PROFILER FALSE CACHE INTERNAL "Use the red engine profiler" FORCE)
else ()
    set(RED_USE_PROFILER ${RED_USE_PROFILER} CACHE INTERNAL "Use the red engine profiler" FORCE)
endif ()

message(STATUS "Use red-engine profiler : ${RED_USE_PROFILER}")
if (RED_USE_PROFILER)
    # Optick Profiler
    target_link_libraries(red_engine_lib
            PRIVATE
            OptickCore)

    target_compile_definitions(red_engine_lib
            PUBLIC
            RED_USE_PROFILER)
endif ()

red_set_compile_definition(red_engine_lib)
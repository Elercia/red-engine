# Filesystem (legacy) dependencies
cmake_minimum_required(VERSION 3.12)

# Debug Library form https://github.com/scottt/debugbreak
add_library(debug_break INTERFACE)

target_include_directories(debug_break INTERFACE DebugBreak)

# Game profiler
add_subdirectory(optick)


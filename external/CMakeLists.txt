# Filesystem (legacy) dependencies
cmake_minimum_required(VERSION 3.12)

# From https://github.com/scottt/debugbreak
add_library(debug_break STATIC DebugBreak/debugbreak.h)
target_include_directories(debug_break PUBLIC DebugBreak)
set_target_properties(debug_break PROPERTIES LINKER_LANGUAGE C)
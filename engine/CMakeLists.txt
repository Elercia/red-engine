cmake_minimum_required(VERSION 3.12)

set(SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INCLUDE_FOLDER_INTERN ${INCLUDE_FOLDER}/RedEngine)

# Include the whole include directory for this directory
include_directories(${INCLUDE_FOLDER})

# Source files
set(SOURCES
    # cmake-format: sortable
    ${SOURCE_FOLDER}/Application.cpp
    ${SOURCE_FOLDER}/Configuration.cpp
    ${SOURCE_FOLDER}/ecs/Component.cpp
      ${SOURCE_FOLDER}/ecs/ComponentManager.cpp
    ${SOURCE_FOLDER}/ecs/Entity.cpp
    ${SOURCE_FOLDER}/ecs/System.cpp
    ${SOURCE_FOLDER}/ecs/World.cpp
    ${SOURCE_FOLDER}/Engine.cpp
    ${SOURCE_FOLDER}/memory/AbstractAllocator.cpp
    ${SOURCE_FOLDER}/memory/MemoryManager.cpp
      ${SOURCE_FOLDER}/memory/MemoryProfiler.cpp
    ${SOURCE_FOLDER}/memory/PoolAllocator.cpp
    ${SOURCE_FOLDER}/systems/RenderingSystem.cpp)

# Headers files
set(HEADERS
    # cmake-format: sortable
    ${INCLUDE_FOLDER_INTERN}/Application.hpp
    ${INCLUDE_FOLDER_INTERN}/Configuration.hpp
    ${INCLUDE_FOLDER_INTERN}/debug/Debug.hpp
    ${INCLUDE_FOLDER_INTERN}/debug/DebugBreak.hpp
    ${INCLUDE_FOLDER_INTERN}/ecs/Component.hpp
      ${INCLUDE_FOLDER_INTERN}/ecs/ComponentManager.hpp
    ${INCLUDE_FOLDER_INTERN}/ecs/Entity.hpp
    ${INCLUDE_FOLDER_INTERN}/ecs/inl/Entity.inl
    ${INCLUDE_FOLDER_INTERN}/ecs/inl/System.inl
    ${INCLUDE_FOLDER_INTERN}/ecs/inl/World.inl
    ${INCLUDE_FOLDER_INTERN}/ecs/System.hpp
    ${INCLUDE_FOLDER_INTERN}/ecs/World.hpp
    ${INCLUDE_FOLDER_INTERN}/Engine.hpp
    ${INCLUDE_FOLDER_INTERN}/inl/Configuration.inl
    ${INCLUDE_FOLDER_INTERN}/memory/AbstractAllocator.hpp
      ${INCLUDE_FOLDER_INTERN}/memory/MemoryProfiler.hpp
    ${INCLUDE_FOLDER_INTERN}/memory/MemoryManager.hpp
    ${INCLUDE_FOLDER_INTERN}/memory/PoolAllocator.hpp
    ${INCLUDE_FOLDER_INTERN}/systems/RenderingSystem.hpp
    ${INCLUDE_FOLDER_INTERN}/Utils.hpp)

# red_engine_lib
add_library(red_engine_lib ${SOURCES} ${HEADERS})
target_include_directories(red_engine_lib SYSTEM INTERFACE ${INCLUDE_FOLDER} PRIVATE "DiligentCore")
target_link_libraries(red_engine_lib 
  PRIVATE
      Diligent-GraphicsEngineD3D11-shared
      Diligent-GraphicsEngineOpenGL-shared
      Diligent-GraphicsEngineD3D12-shared
      Diligent-GraphicsEngineVk-shared)

target_compile_options(
  red_engine_lib
  PRIVATE -DUNICODE -DENGINE_DLL
          -Wall
          -Wextra
          -Wshadow
          -Wnon-virtual-dtor
          -Wold-style-cast
          -Wcast-align
          -Wunused
          -Woverloaded-virtual
          -Wconversion
          -fno-exceptions
          -O0)

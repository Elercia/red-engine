cmake_minimum_required(VERSION 3.12)

set(SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INCLUDE_FOLDER_INTERN ${INCLUDE_FOLDER}/RedEngine)

# Include the whole include directory for this directory
include_directories(${INCLUDE_FOLDER})

# Source files
set(SOURCES
        ${SOURCE_FOLDER}/Application.cpp
        ${SOURCE_FOLDER}/Window.cpp
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
        ${SOURCE_FOLDER}/systems/RenderingSystem.cpp
        ${SOURCE_FOLDER}/engine/RenderingEngine.cpp
        ${SOURCE_FOLDER}/components/Mesh.cpp)

# Headers files
set(HEADERS
        # cmake-format: sortable
        ${INCLUDE_FOLDER_INTERN}/Application.hpp
        ${INCLUDE_FOLDER_INTERN}/Window.hpp
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
        ${INCLUDE_FOLDER_INTERN}/engine/RenderingEngine.hpp
        ${INCLUDE_FOLDER_INTERN}/Utils.hpp
        ${INCLUDE_FOLDER_INTERN}/Platform.hpp
        ${INCLUDE_FOLDER_INTERN}/components/Mesh.hpp)

# red_engine_lib
add_library(red_engine_lib ${SOURCES} ${HEADERS})

# Diligent engine linking 
target_include_directories(red_engine_lib PUBLIC "../external/" ${INCLUDE_FOLDER_INTERN} ${INCLUDE_FOLDER})

target_compile_definitions(red_engine_lib
        PUBLIC
        UNICODE
        ENGINE_DLL=1
        D3D11_SUPPORTED=$<BOOL:${D3D11_SUPPORTED}>
        D3D12_SUPPORTED=$<BOOL:${D3D12_SUPPORTED}>
        GL_SUPPORTED=$<BOOL:${GL_SUPPORTED}>
        VULKAN_SUPPORTED=$<BOOL:${VULKAN_SUPPORTED}>
        )

if (!WIN32)
    message(FATAL_ERROR "Only Win32 is supported now")
endif ()

target_compile_definitions(red_engine_lib
        PUBLIC
        PLATFORM_WIN32=1)

if (D3D11_SUPPORTED)
    target_link_libraries(red_engine_lib PRIVATE Diligent-GraphicsEngineD3D11-shared)
endif ()
if (D3D12_SUPPORTED)
    target_link_libraries(red_engine_lib PRIVATE Diligent-GraphicsEngineD3D12-shared)
endif ()
if (GL_SUPPORTED)
    target_link_libraries(red_engine_lib PRIVATE Diligent-GraphicsEngineOpenGL-shared)
endif ()
if (VULKAN_SUPPORTED)
    target_link_libraries(red_engine_lib PRIVATE Diligent-GraphicsEngineVk-shared)
endif ()
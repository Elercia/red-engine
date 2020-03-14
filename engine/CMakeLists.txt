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
        ${INCLUDE_FOLDER_INTERN}/components/Mesh.hpp ${INCLUDE_FOLDER_INTERN}/log/Logger.hpp ${INCLUDE_FOLDER_INTERN}/log/inl/Logger.inl)

# red_engine_lib
add_library(red_engine_lib STATIC ${SOURCES} ${HEADERS})

# SLD2
target_link_libraries(red_engine_lib PUBLIC SDL2::SDL2 SDL2::SDL2main)

# FMT
target_link_libraries(red_engine_lib PUBLIC fmt-header-only)

# Diligent engine linking
set_common_target_properties(red_engine_lib)
set_target_properties(red_engine_lib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_include_directories(red_engine_lib
        PUBLIC
        ${INCLUDE_FOLDER_INTERN}
        ${INCLUDE_FOLDER}
        "../external/" )

if(MSVC)
target_compile_options(red_engine_lib PRIVATE -DUNICODE)

if(PLATFORM_UNIVERSAL_WINDOWS)
    # Disable w4189: local variable is initialized but not referenced
    # Disable w4063: case is not a valid value for switch of enum
    # Consume the windows runtime extensions (/ZW)
    target_compile_options(red_engine_lib INTERFACE /wd4189 /wd4063 /ZW)
endif(PLATFORM_UNIVERSAL_WINDOWS)
endif(MSVC)

get_supported_backends(DILIGENT_ENGINE_LIBRARIES)

target_link_libraries(red_engine_lib
    PRIVATE
        Diligent-BuildSettings
    PUBLIC
        Diligent-Common
        Diligent-GraphicsTools
        Diligent-TargetPlatform
        ${DILIGENT_ENGINE_LIBRARIES}
    )

if(PLATFORM_UNIVERSAL_WINDOWS)
    target_link_libraries(red_engine_lib PRIVATE dxguid.lib)
elseif(PLATFORM_ANDROID)
    target_link_libraries(red_engine_lib PRIVATE GLESv3 PUBLIC native_app_glue)
elseif(PLATFORM_LINUX)
    target_link_libraries(red_engine_lib PRIVATE GL X11)
elseif(PLATFORM_MACOS OR PLATFORM_IOS)
endif()



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

# red_engine_lib
add_library(red_engine_lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(red_engine_lib
        PUBLIC
        ${INCLUDE_FOLDER_INTERN}
        ${INCLUDE_FOLDER}
        "../external/")

# SLD2
target_link_libraries(red_engine_lib
        PUBLIC
        SDL2::SDL2
        SDL2::SDL2main)

# Diligent engine linking

if (MSVC)
    target_compile_options(red_engine_lib PRIVATE -DUNICODE)

    if (PLATFORM_UNIVERSAL_WINDOWS)
        # Disable w4189: local variable is initialized but not referenced
        # Disable w4063: case is not a valid value for switch of enum
        # Consume the windows runtime extensions (/ZW)
        target_compile_options(red_engine_lib INTERFACE /wd4189 /wd4063 /ZW)
    endif (PLATFORM_UNIVERSAL_WINDOWS)
endif (MSVC)

get_supported_backends(DILIGENT_ENGINE_LIBRARIES)

target_link_libraries(red_engine_lib
        PRIVATE
        Diligent-BuildSettings
        PUBLIC
        Diligent-Common
        Diligent-TargetPlatform
        Diligent-GraphicsTools
        Diligent-TargetPlatform
        ${DILIGENT_ENGINE_LIBRARIES}
        )

if (PLATFORM_UNIVERSAL_WINDOWS)
    target_link_libraries(red_engine_lib PRIVATE dxguid.lib)
elseif (PLATFORM_ANDROID)
    target_link_libraries(red_engine_lib PRIVATE GLESv3 PUBLIC native_app_glue)
elseif (PLATFORM_LINUX)
    target_link_libraries(red_engine_lib PRIVATE GL X11)
elseif (PLATFORM_MACOS OR PLATFORM_IOS)
endif ()

# Project options and warning
target_link_libraries(red_engine_lib
        INTERFACE
        red_project_options
        red_project_warnings)

target_compile_definitions(red_engine_lib
        PUBLIC
        ENGINE_DLL=0)



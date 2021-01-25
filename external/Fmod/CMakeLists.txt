cmake_minimum_required(VERSION 3.12)

set( LIB_FMOD_CORE "${CMAKE_CURRENT_SOURCE_DIR}/core/lib/x64/fmod_vc.lib" )
set( DLL_FMOD_CORE "${CMAKE_CURRENT_SOURCE_DIR}/core/lib/x64/fmod.dll" )
set( LIB_FMOD_STUDIO "${CMAKE_CURRENT_SOURCE_DIR}/studio/lib/x64/fmodstudio_vc.lib" )
set( DLL_FMOD_STUDIO "${CMAKE_CURRENT_SOURCE_DIR}/studio/lib/x64/fmodstudio.dll" )

add_library( fmodCore SHARED IMPORTED )
set_target_properties(
        fmodCore PROPERTIES
        IMPORTED_LOCATION ${DLL_FMOD_CORE}
        IMPORTED_IMPLIB ${LIB_FMOD_CORE}
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/core/inc
        DEFINE_SYMBOL BLABLA
        )

add_library( fmodStudio SHARED IMPORTED )
set_target_properties(
        fmodStudio PROPERTIES
        IMPORTED_LOCATION ${DLL_FMOD_STUDIO}
        IMPORTED_IMPLIB ${LIB_FMOD_STUDIO}
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/studio/inc/
        )

add_library(fmod empty.cpp)

target_link_libraries(fmod PUBLIC fmodCore fmodStudio)

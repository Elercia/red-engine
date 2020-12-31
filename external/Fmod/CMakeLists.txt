cmake_minimum_required(VERSION 3.18)

project(FMOD CXX C)

set( LIB_FMOD_CORE "${CMAKE_CURRENT_SOURCE_DIR}/core/lib/x64/fmod_vc.lib" )
set( DLL_FMOD_CORE "${CMAKE_CURRENT_SOURCE_DIR}/core/lib/x64/fmod.dll" )
set( LIB_FMOD_STUDIO "${CMAKE_CURRENT_SOURCE_DIR}/studio/lib/x64/fmodstudio_vc.lib" )
set( DLL_FMOD_STUDIO "${CMAKE_CURRENT_SOURCE_DIR}/studio/lib/x64/fmodstudio.dll" )

add_library( FmodCore SHARED IMPORTED GLOBAL)
set_target_properties(
        FmodCore PROPERTIES
        IMPORTED_LOCATION ${DLL_FMOD_CORE}
        IMPORTED_IMPLIB ${LIB_FMOD_CORE}
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/core/inc"
        )

add_library( FmodStudio SHARED IMPORTED GLOBAL)
set_target_properties(
        FmodStudio PROPERTIES
        IMPORTED_LOCATION ${DLL_FMOD_STUDIO}
        IMPORTED_IMPLIB ${LIB_FMOD_STUDIO}
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/studio/inc/"
        )
target_link_libraries(FmodStudio INTERFACE FmodCore)

file(COPY ${DLL_FMOD_CORE}
    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(COPY ${DLL_FMOD_STUDIO}
    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
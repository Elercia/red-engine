cmake_minimum_required(VERSION 3.12)

set(FMOD_INCLUDE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# Headers files
file(GLOB_RECURSE FMOD_HEADERS
        ${FMOD_INCLUDE_FOLDER}/*.hpp
        )

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64 bits
    set( LIB_FMOD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/*.*" )
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # 32 bits
    set( LIB_FMOD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/x86/*.*" )
endif()

file(GLOB_RECURSE FMOD_LIBS
        ${LIB_FMOD_DIR}/*.*
        )

add_library(fmod SHARED ${FMOD_HEADERS})
    
#set_target_properties(
#        fmod PROPERTIES
#        IMPORTED_LOCATION   ${LIB_FMOD}
#        INTERFACE_INCLUDE_DIRECTORIES ${FMOD_INCLUDE_FOLDER}
#        )

target_link_libraries(fmod PUBLIC ${FMOD_LIBS})

target_include_directories(fmod PUBLIC ${FMOD_INCLUDE_FOLDER})

set_target_properties(fmod PROPERTIES LINKER_LANGUAGE CXX)
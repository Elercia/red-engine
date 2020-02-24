cmake_minimum_required(VERSION 3.12)

if (!WIN32)
	message(FATAL_ERROR "Not a Win32 platform")
endif()

set(HEADERS src/CustomSystem.hpp
		src/CustomComponent.hpp)

set(SOURCES src/main.cpp
		src/CustomSystem.cpp)

set(PROJECT_SOURCES ${HEADERS} ${SOURCES})

add_executable(TemplateSimple WIN32 
		${PROJECT_SOURCES})

set_target_properties(TemplateSimple PROPERTIES
    FOLDER ../../ressources
)

target_link_libraries(TemplateSimple PRIVATE red_engine_lib)

copy_required_dlls(TemplateSimple)


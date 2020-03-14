cmake_minimum_required(VERSION 3.12)

set(HEADERS src/CustomSystem.hpp
		src/CustomComponent.hpp)

set(SOURCES src/main.cpp
		src/CustomSystem.cpp)

set(PROJECT_SOURCES ${HEADERS} ${SOURCES})

add_executable(TemplateSimple
		${PROJECT_SOURCES})

set_target_properties(TemplateSimple PROPERTIES
    FOLDER ../../ressources
)

target_link_libraries(TemplateSimple PUBLIC red_engine_lib)

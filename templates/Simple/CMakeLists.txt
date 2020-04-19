cmake_minimum_required(VERSION 3.12)

set(HEADERS src/CustomSystem.hpp
        src/CustomComponent.hpp)

set(SOURCES src/main.cpp
        src/CustomSystem.cpp)

file(GLOB SHADERS resources/*.sc)

set(PROJECT_SOURCES ${HEADERS} ${SOURCES})

add_executable(TemplateSimple
        ${PROJECT_SOURCES}
        ${SHADERS})

set_target_properties(TemplateSimple PROPERTIES
        FOLDER ../../ressources
        )

target_link_libraries(TemplateSimple PUBLIC red_engine_lib)
red_add_template(TemplateSimple resources OPENGLES)
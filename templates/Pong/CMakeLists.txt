cmake_minimum_required(VERSION 3.12)


file(GLOB HEADERS src/*.hpp)
file(GLOB SOURCES src/*.cpp)
file(GLOB SHADERS resources/*.sc)

set(PROJECT_SOURCES ${HEADERS} ${SOURCES})

add_executable(TemplatePong
        ${PROJECT_SOURCES}
        ${SHADERS})

set_target_properties(TemplatePong PROPERTIES
        FOLDER ../../ressources
        )

target_link_libraries(TemplatePong PUBLIC red_engine_lib)
red_add_template(TemplatePong resources)
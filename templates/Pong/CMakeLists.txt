cmake_minimum_required(VERSION 3.18)


file(GLOB HEADERS src/*.hpp)
file(GLOB SOURCES src/*.cpp)

set(PROJECT_SOURCES ${HEADERS} ${SOURCES})

add_executable(TemplatePong
        ${PROJECT_SOURCES})

set_target_properties(TemplatePong PROPERTIES
        FOLDER ../../ressources
        )

target_link_libraries(TemplatePong PUBLIC red_engine_lib)

set_property(TARGET TemplatePong PROPERTY FOLDER "templates")

red_add_template(TemplatePong ${CMAKE_CURRENT_SOURCE_DIR})
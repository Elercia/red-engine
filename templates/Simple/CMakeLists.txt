cmake_minimum_required(VERSION 3.12)


add_executable(TemplateSimple src/main.cpp
		src/CustomSystem.cpp
		src/CustomSystem.hpp
		src/CustomComponent.hpp)

target_link_libraries(TemplateSimple red_engine_lib)
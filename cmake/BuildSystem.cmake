# Add all the custom projects
foreach (p ${BUILDSYSTEM_PROJECTS_DIR})
    add_subdirectory(${p})
endforeach (p ${})

#Linting
find_program(CPPLINT_EXE NAMES "cpplint")
if (CPPLINT_EXE)
    set(CMAKE_C_CPPLINT "${CPPLINT_EXE};--quiet")
    set(CMAKE_CXX_CPPLINT "${CPPLINT_EXE};--quiet")
endif ()

#Clang tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if (CLANG_TIDY_EXE)
    set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_EXE};-p=compile_commands.json")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-p=compile_commands.json")
endif ()

#CPP Check
find_program(CPPCHECK_EXE NAMES "cppcheck")
if (CPPCHECK_EXE)
    set(CMAKE_C_CPPCHECK "${CPPCHECK_EXE};--project=compile_commands.json;--enable=all;--inconclusive;--inline-suppr;\
--suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck-suppressions.txt;-D__GNUC__;-i ${PROJECT_SOURCE_DIR}/build")
    set(CMAKE_CXX_CPPCHECK "${CPPCHECK_EXE};--project=compile_commands.json;--enable=all;--inconclusive;--inline-suppr;\
--suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck-suppressions.txt;-D__GNUC__;-i ${PROJECT_SOURCE_DIR}/build")
endif ()

#Include What You Use (need more config)
find_program(IWYU_EXE NAMES "iwyu")
if (IWYU_EXE)
    #set(CMAKE_C_INCLUDE_WHAT_YOU_USE "${IWYU_EXE}")
    #set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${IWYU_EXE}")
endif ()

#Enforce using Link What You Use
set(CMAKE_LINK_WHAT_YOU_USE TRUE)

#Custom target for formatting our code
find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if (CLANG_FORMAT_EXE)
    file(GLOB_RECURSE FILES_TO_FORMAT ${PROJECTS_DIR})
    add_custom_target(
            clangformat COMMAND ${CLANG_FORMAT_EXE}
            -style=file
            -i
            ${FILES_TO_FORMAT}
    )
endif ()
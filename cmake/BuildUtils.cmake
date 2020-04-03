function(red_add_template _TARGET _RESOURCE_FOLDER)

    set_target_properties(${_TARGET}
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/template-${_TARGET}/"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/template-${_TARGET}/"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/template-${_TARGET}/"
            )

    add_custom_command(TARGET ${_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${_RESOURCE_FOLDER} $<TARGET_FILE_DIR:${_TARGET}>/${_RESOURCE_FOLDER})

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")

        set(OPTICK_CORE_BASE $<TARGET_FILE_DIR:OptickCore>)

        set(OPTICK_CORE_FILES ${OPTICK_CORE_BASE}/OptickCored.dll ${OPTICK_CORE_BASE}/OptickCored.ilk)

        add_custom_command(TARGET ${_TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${OPTICK_CORE_FILES} $<TARGET_FILE_DIR:${_TARGET}>)

        add_dependencies(${_TARGET} OptickCore)
    endif ()

endfunction()

function(red_set_compile_definition pTARGET)

    if (MSVC OR MSYS OR MINGW) # Windows Platform
        set(PLATFORM PLATFORM_WINDOWS)
    elseif (APPLE) # Apple platform
        set(PLATFORM PLATFORM_APPLE)
    elseif(UNIX AND NOT APPLE) # Linux
        set(PLATFORM PLATFORM_LINUX)
    endif ()

    target_compile_definitions(${pTARGET} PUBLIC ${PLATFORM})

    # Warnings & stuff
    target_link_libraries(${pTARGET} 
    	PUBLIC
        red_project_warnings
        red_project_options)
    
endfunction()

function(red_add_template _TARGET _WORKING_DIR)

    set_property(TARGET ${_TARGET} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${_WORKING_DIR})

    red_set_compile_definition(${_TARGET})

endfunction(red_add_template)

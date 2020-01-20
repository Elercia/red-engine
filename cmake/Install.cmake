SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_NAME})
SET(CPACK_PACKAGE_VENDOR "VALERE91 <valereplantevin@gmail.com>")
SET(CPACK_PACKAGE_DESCRIPTION_FILE ${PROJECT_SOURCE_DIR}/README.md)
SET(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/LICENSE)
SET(CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH})
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
IF (WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backlasshes.
    SET(CPACK_PACKAGE_ICON ${PROJECT_SOURCE_DIR}/resources/install\\\\InstallIcon.png)
    SET(CPACK_NSIS_INSTALLED_ICON_NAME ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin\\\\model_viewer.exe)
    SET(CPACK_NSIS_DISPLAY_NAME ${PROJECT_NAME})
    SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
    SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
    SET(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
    SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE (WIN32 AND NOT UNIX)
    SET(CPACK_STRIP_FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin\\\\model_viewer)
    SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF (WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES model_viewer "Model viewer")
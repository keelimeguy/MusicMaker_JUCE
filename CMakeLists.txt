cmake_minimum_required( VERSION 3.17.2 )


####################################################################
# Define meta info
####################################################################

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    option( WINDOWS_VS "Using Windows Visual Studio" ON )
else()
    option( WINDOWS_VS "Using Windows Visual Studio" OFF )
    set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
endif()

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib ) # Output directory for static lib (.LIB) (.A)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for shared lib (.DLL)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for executables (.EXE)

if( NOT CMAKE_BUILD_TYPE )
    set ( CMAKE_BUILD_TYPE Release )
endif()


####################################################################
# Build projects
####################################################################

include( build_project_main.cmake )


####################################################################
# Additional setup for Visual Studio
####################################################################

if( WINDOWS_VS )
    set_directory_properties( PROPERTIES
        VS_STARTUP_PROJECT main
    )

    # Tell Visual Studio to run through console (not as a Windows app)
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE" )
endif()

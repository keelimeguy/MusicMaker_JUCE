cmake_minimum_required( VERSION 3.17.2 )


####################################################################
# Define meta info
####################################################################

project( AudioProject )

set( CMAKE_CXX_STANDARD 17 )

if( MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX" )
else()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror" )
    set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
endif()

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib ) # Output directory for static lib (.LIB) (.A)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for shared lib (.DLL)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for executables (.EXE)

if( NOT CMAKE_BUILD_TYPE )
    set ( CMAKE_BUILD_TYPE Debug )
endif()


####################################################################
# Build projects
####################################################################

include( build_project_main.cmake )


####################################################################
# Additional setup for Visual Studio
####################################################################

if( MSVC )
    set_directory_properties( PROPERTIES
        VS_STARTUP_PROJECT main
    )

    # Tell Visual Studio to run through console (not as a Windows app)
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE" )
endif()

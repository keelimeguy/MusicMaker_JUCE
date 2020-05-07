cmake_minimum_required( VERSION 3.17.2 )


####################################################################
# Define meta info
####################################################################

project( AudioProject )

set( CMAKE_CXX_STANDARD 17 )

if( MSVC )
    # # Tell Visual Studio to run through console (not as a Windows app)
    # set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE" )

else()
    # Export the 'compile_commands.json' file
    set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

endif()

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib ) # Output directory for static lib (.LIB) (.A)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for shared lib (.DLL)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for executables (.EXE)

if( NOT DEFINED CMAKE_CONFIGURATION_TYPES )
    if( NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "" )
        set( CMAKE_BUILD_TYPE Debug )
        message( STATUS "Setting CMAKE_BUILD_TYPE to \"${CMAKE_BUILD_TYPE}\" as it was not specified." )
    endif()
endif()


####################################################################
# Build project
####################################################################

add_subdirectory( vendor )

include_jucer_file( ${JUCE_VENDOR_DIR}/JUCE/examples/DemoRunner/DemoRunner.jucer )


####################################################################
# Additional setup for Visual Studio
####################################################################

if( MSVC )
    set_directory_properties( PROPERTIES
        VS_STARTUP_PROJECT DemoRunner
    )
endif()

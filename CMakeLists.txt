cmake_minimum_required( VERSION 3.17.2 )


####################################################################
# User options
####################################################################

# Set defaults:
option( AUTO_BUILD_FRUT "Build the FRUT sub-repository automatically" ON )
option( VENDOR_BUILD_DEMORUNNER "Build the DemoRunner example JUCE project" OFF )
option( USE_DEMORUNNER_BIGOBJ_FIX "Add big-obj flags to fix large file errors in DemoRunner" ON )


####################################################################
# Define meta info
####################################################################

project( AudioProject )

set( CMAKE_CXX_STANDARD 17 )

if( NOT MSVC )
    # Export the 'compile_commands.json' file
    set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
endif()

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib ) # Output directory for static lib (.LIB) (.A)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for shared lib (.DLL)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for executables (.EXE)

set( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/install CACHE PATH "" FORCE )
message( STATUS "CMAKE_INSTALL_PREFIX is set to: ${CMAKE_INSTALL_PREFIX}" )

####################################################################
# Build projects
####################################################################

add_subdirectory( vendor )

if( VENDOR_BUILD_DEMORUNNER )
    build_demorunner()
endif()

add_custom_target( distclean
    COMMAND echo "try running:   rm -r ${CMAKE_BINARY_DIR}"
    COMMAND echo "               rm -r ${CMAKE_CURRENT_LIST_DIR}/install"
    DEPENDS clean_juce
)

####################################################################
# Additional setup for Visual Studio
####################################################################

if( MSVC )
    if( VENDOR_BUILD_DEMORUNNER )
        set_directory_properties( PROPERTIES
            VS_STARTUP_PROJECT DemoRunner
        )
    endif()
endif()

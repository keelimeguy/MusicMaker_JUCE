cmake_minimum_required( VERSION 3.17.2 )


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

cmake_minimum_required( VERSION 3.17.2 )

project( juce VERSION 5.4.7 LANGUAGES CXX )

execute_process(
    COMMAND git submodule update --init JUCE FRUT
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

set( JUCE_VENDOR_DIR ${CMAKE_CURRENT_LIST_DIR}
    CACHE PATH "JUCE vendor directory"
)

file( MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/FRUT/build )

####################################################################

function( include_jucer_file jucer_file )

    get_filename_component( jucer_file_dir ${jucer_file} DIRECTORY )
    get_filename_component( jucer_file_name ${jucer_file} NAME_WLE )
    file( MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${jucer_file_name} )

    # Build the subrepo
    message( "building: FRUT" )
    execute_process(
        COMMAND cmake -S FRUT -B FRUT/build -DCMAKE_INSTALL_PREFIX=FRUT/install -DJUCE_ROOT=${JUCE_VENDOR_DIR}/JUCE
        COMMAND cmake --build FRUT/build --target install
        WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
    )

    # Apply fixes to subrepo so that it runs without error
    message( "fixing: FRUT" )
    if( WIN32 AND NOT MSVC )
        # Fix generator check to allow Unix Makefiles on a Windows platform
        execute_process(
            COMMAND sed -i "57s/.*/  \"CMAKE_HOST_SYSTEM_NAME\\\\;STREQUAL\\\\;Linux\\\\;AND\\\\;NOT\\\\;CMAKE_EXTRA_GENERATOR\\\\;STREQUAL\\\\;CodeBlocks\\\\;OR\\\\;CMAKE_GENERATOR\\\\;MATCHES\\\\;Unix Makefiles\"/g" FRUT/install/FRUT/cmake/Reprojucer.cmake
            WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
        )
        execute_process(
            COMMAND sed -i "58s/.*/  \"WIN32\\\\;AND\\\\;NOT\\\\;MSVC\\\\;AND\\\\;NOT\\\\;CMAKE_GENERATOR\\\\;MATCHES\\\\;Unix Makefiles\"/g" FRUT/install/FRUT/cmake/Reprojucer.cmake
            WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
        )
    endif()

    # Generate the cmake file
    message( "convert_jucer_to_cmake: ${jucer_file}" )
    execute_process(
        COMMAND ${JUCE_VENDOR_DIR}/FRUT/install/FRUT/bin/Jucer2Reprojucer ${jucer_file} ${JUCE_VENDOR_DIR}/FRUT/install/FRUT/cmake/Reprojucer.cmake --juce-modules ${JUCE_VENDOR_DIR}/JUCE/modules
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${jucer_file_name}
    )

    # Build the generated cmake file
    add_subdirectory( ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${jucer_file_name} )

endfunction()

####################################################################

function( build_demorunner )

    if( MSVC )
        # Add /bigobj flag to MSVC compilations in DemoRunner
        execute_process(
            COMMAND sed -i "183s|.*|            extraCompilerFlags=\"/w44265 /w45038 /w44062 /bigobj\">|g" JUCE/examples/DemoRunner/DemoRunner.jucer
            WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
        )
        execute_process(
            COMMAND sed -i "212s|.*|            extraCompilerFlags=\"/w44265 /w45038 /w44062 /bigobj\">|g" JUCE/examples/DemoRunner/DemoRunner.jucer
            WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
        )
    endif()

    include_jucer_file( ${JUCE_VENDOR_DIR}/JUCE/examples/DemoRunner/DemoRunner.jucer )

    set( DEMORUNNER_ASSETS
        ${JUCE_VENDOR_DIR}/JUCE/examples/Assets
        ${JUCE_VENDOR_DIR}/JUCE/examples/Audio
        ${JUCE_VENDOR_DIR}/JUCE/examples/BLOCKS
        ${JUCE_VENDOR_DIR}/JUCE/examples/DSP
        ${JUCE_VENDOR_DIR}/JUCE/examples/GUI
        ${JUCE_VENDOR_DIR}/JUCE/examples/Plugins
        ${JUCE_VENDOR_DIR}/JUCE/examples/Utilities
    )
    install( DIRECTORY ${DEMORUNNER_ASSETS} DESTINATION DemoRunner/examples )
    install( PROGRAMS $<TARGET_FILE:DemoRunner> DESTINATION DemoRunner )

endfunction()

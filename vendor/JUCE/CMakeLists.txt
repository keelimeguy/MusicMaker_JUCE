cmake_minimum_required( VERSION 3.17.2 )

project( juce VERSION 5.4.7 LANGUAGES CXX )

execute_process(
    COMMAND git submodule update --init JUCE FRUT
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

set( JUCE_VENDOR_DIR ${CMAKE_CURRENT_LIST_DIR}
    CACHE PATH "JUCE vendor directory"
)

file( MAKE_DIRECTORY ${JUCE_VENDOR_DIR}/FRUT/build )

add_custom_target( clean_frut
    COMMAND echo "try running:   rm -r ${JUCE_VENDOR_DIR}/FRUT/build"
    COMMAND echo "               rm -r ${JUCE_VENDOR_DIR}/FRUT/install"
)

add_custom_target( clean_juce
    DEPENDS clean_frut
)

####################################################################

function( include_jucer_file jucer_file fix_target_is_defined )

    get_filename_component( jucer_file_dir ${jucer_file} DIRECTORY )
    get_filename_component( jucer_file_name ${jucer_file} NAME_WLE )
    file( MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${jucer_file_name}_cmake )

    if( AUTO_BUILD_FRUT )
        # Build the subrepo
        message( STATUS "building: FRUT" )
        execute_process(
            COMMAND cmake -S FRUT -B FRUT/build -DCMAKE_INSTALL_PREFIX=FRUT/install -DJUCE_ROOT=${JUCE_VENDOR_DIR}/JUCE
            WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
        )
        execute_process(
            COMMAND cmake --build FRUT/build --target install
            WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
        )
    else()
        message( "WARNING: Skipping automatic build of FRUT dependency." )
    endif()

    execute_process(
        COMMAND sed -i "/target_include_directories(\${.*} SYSTEM/b; s/target_include_directories(\${.*}/& SYSTEM/g" FRUT/install/FRUT/cmake/Reprojucer.cmake
        WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
    )

    # Generate the cmake file
    message( STATUS "convert_jucer_to_cmake: ${jucer_file}" )
    execute_process(
        COMMAND ${JUCE_VENDOR_DIR}/FRUT/install/FRUT/bin/Jucer2Reprojucer ${jucer_file} ${JUCE_VENDOR_DIR}/FRUT/install/FRUT/cmake/Reprojucer.cmake --juce-modules ${JUCE_VENDOR_DIR}/JUCE/modules
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${jucer_file_name}_cmake
    )

    if( fix_target_is_defined )
        execute_process(
            COMMAND sed -i "$ a include( ${jucer_file_dir}/fix_target_${jucer_file_name}.cmake )" CMakeLists.txt
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${jucer_file_name}_cmake
        )
        execute_process(
            COMMAND sed -i "$ a fix_target_${jucer_file_name}()" CMakeLists.txt
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${jucer_file_name}_cmake
        )
    endif()

    # Build the generated cmake file
    add_subdirectory( ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${jucer_file_name}_cmake )

endfunction()

####################################################################

function( build_demorunner )

    if( USE_DEMORUNNER_BIGOBJ_FIX )
        # Add big-obj flags to fix large file errors
        if( MSVC )
            execute_process(
                COMMAND sed -i "183s|.*|            extraCompilerFlags=\"/w44265 /w45038 /w44062 /bigobj\">|g" JUCE/examples/DemoRunner/DemoRunner.jucer
                WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
            )
            execute_process(
                COMMAND sed -i "212s|.*|            extraCompilerFlags=\"/w44265 /w45038 /w44062 /bigobj\">|g" JUCE/examples/DemoRunner/DemoRunner.jucer
                WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
            )
        else()
            execute_process(
                COMMAND sed -i "62s|.*|    <LINUX_MAKE targetFolder=\"Builds/LinuxMakefile\" smallIcon=\"YyqWd2\" bigIcon=\"YyqWd2\" extraCompilerFlags=\"-Wa,-mbig-obj\">|g" JUCE/examples/DemoRunner/DemoRunner.jucer
                WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
            )
        endif()
    else()
        # Otherwise, since the files may have changed, make sure big-obj flags aren't used
        if( MSVC )
            execute_process(
                COMMAND sed -i "183s|.*|            extraCompilerFlags=\"/w44265 /w45038 /w44062\">|g" JUCE/examples/DemoRunner/DemoRunner.jucer
                WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
            )
            execute_process(
                COMMAND sed -i "212s|.*|            extraCompilerFlags=\"/w44265 /w45038 /w44062\">|g" JUCE/examples/DemoRunner/DemoRunner.jucer
                WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
            )
        else()
            execute_process(
                COMMAND sed -i "62s|.*|    <LINUX_MAKE targetFolder=\"Builds/LinuxMakefile\" smallIcon=\"YyqWd2\" bigIcon=\"YyqWd2\">|g" JUCE/examples/DemoRunner/DemoRunner.jucer
                WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
            )
        endif()
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

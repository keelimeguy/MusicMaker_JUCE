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
file( MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin )
function(include_jucer_file jucer_file)
    message( "building: FRUT" )
    execute_process(
        COMMAND cmake -S FRUT -B FRUT/build -DCMAKE_INSTALL_PREFIX=FRUT/install -DJUCE_ROOT=${JUCE_VENDOR_DIR}/JUCE
        COMMAND cmake --build FRUT/build --target install
        WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
    )
    message( "fixing: FRUT" )
    if( MSVC )
        execute_process(
            COMMAND sed -i "183s|.*|            extraCompilerFlags=\"/w44265 /w45038 /w44062 /bigobj\">|g" JUCE/examples/DemoRunner/DemoRunner.jucer
            WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
        )
    else()
        execute_process(
            COMMAND sed -i "57s/.*/  \"CMAKE_HOST_SYSTEM_NAME\\\\;STREQUAL\\\\;Linux\\\\;AND\\\\;NOT\\\\;CMAKE_EXTRA_GENERATOR\\\\;STREQUAL\\\\;CodeBlocks\\\\;OR\\\\;CMAKE_GENERATOR\\\\;MATCHES\\\\;Unix Makefiles\"/g" FRUT/install/FRUT/cmake/Reprojucer.cmake
            WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
        )
        execute_process(
            COMMAND sed -i "58s/.*/  \"WIN32\\\\;AND\\\\;NOT\\\\;MSVC\\\\;AND\\\\;NOT\\\\;CMAKE_GENERATOR\\\\;MATCHES\\\\;Unix Makefiles\"/g" FRUT/install/FRUT/cmake/Reprojucer.cmake
            WORKING_DIRECTORY ${JUCE_VENDOR_DIR}
        )
    endif()
    message( "convert_jucer_to_cmake: ${jucer_file}" )
    execute_process(
        COMMAND ../FRUT/install/FRUT/bin/Jucer2Reprojucer ${jucer_file} ../FRUT/install/FRUT/cmake/Reprojucer.cmake
        WORKING_DIRECTORY ${JUCE_VENDOR_DIR}/bin
    )
    add_subdirectory( ${JUCE_VENDOR_DIR}/bin )
endfunction()

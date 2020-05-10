cmake_minimum_required( VERSION 3.17.2 )

project( MusicMaker )

include_jucer_file( ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.jucer )

target_precompile_headers( ${PROJECT_NAME}
    PUBLIC
        src/pch.h
)

target_link_libraries( ${PROJECT_NAME}
    PUBLIC
        spdlog
)

# Disable all warnings when compiling JUCE modules
set( JUCE_modules_sources
    ${JUCER_PROJECT_MODULE_juce_audio_basics_SOURCES}
    ${JUCER_PROJECT_MODULE_juce_audio_devices_SOURCES}
    ${JUCER_PROJECT_MODULE_juce_audio_formats_SOURCES}
    ${JUCER_PROJECT_MODULE_juce_audio_processors_SOURCES}
    ${JUCER_PROJECT_MODULE_juce_audio_utils_SOURCES}
    ${JUCER_PROJECT_MODULE_juce_core_SOURCES}
    ${JUCER_PROJECT_MODULE_juce_data_structures_SOURCES}
    ${JUCER_PROJECT_MODULE_juce_events_SOURCES}
    ${JUCER_PROJECT_MODULE_juce_graphics_SOURCES}
    ${JUCER_PROJECT_MODULE_juce_gui_basics_SOURCES}
    ${JUCER_PROJECT_MODULE_juce_gui_extra_SOURCES}
)

if( MSVC )
    set_source_files_properties( ${JUCE_modules_sources} PROPERTIES COMPILE_FLAGS "/W0" )
else()
    set_source_files_properties( ${JUCE_modules_sources} PROPERTIES COMPILE_FLAGS "-w" )
endif()

install( PROGRAMS $<TARGET_FILE:${PROJECT_NAME}> DESTINATION ${PROJECT_NAME} )

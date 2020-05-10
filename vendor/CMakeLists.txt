cmake_minimum_required( VERSION 3.17.2 )

find_library( spdlog_LIBRARY_RELEASE NAMES spdlog HINTS "${CMAKE_CURRENT_LIST_DIR}/spdlog/bin" )

add_subdirectory( JUCE )
add_subdirectory( spdlog )

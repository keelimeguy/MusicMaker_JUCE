cmake_minimum_required( VERSION 3.17.2 )

include_jucer_file( ${CMAKE_CURRENT_LIST_DIR}/MusicMaker.jucer )
install( PROGRAMS $<TARGET_FILE:MusicMaker> DESTINATION MusicMaker )

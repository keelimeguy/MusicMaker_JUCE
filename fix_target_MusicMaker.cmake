cmake_minimum_required( VERSION 3.17.2 )

project( MusicMaker )

file( GLOB_RECURSE ${PROJECT_NAME}_sources ${CMAKE_CURRENT_LIST_DIR}/src/* )
set( root_list_dir ${CMAKE_CURRENT_LIST_DIR} )

function( fix_target_${PROJECT_NAME} )

    if( RUN_CLANG_TIDY )
        apply_clang_tidy_to_project( ${PROJECT_NAME} )
    endif()

    get_target_property( vendor_sources ${PROJECT_NAME} SOURCES )
    set_source_files_properties( ${PROJECT_NAME} PROPERTIES SOURCES "" )
    list( REMOVE_ITEM vendor_sources ${${PROJECT_NAME}_sources} )

    set( resource_sources
        ${${PROJECT_NAME}_BINARY_DIR}/resources.rc
    )
    list( REMOVE_ITEM vendor_sources ${resource_sources} )

    get_target_property( ${PROJECT_NAME}_BINARY_DIR ${PROJECT_NAME} BINARY_DIR )
    set( pch_sources
        ${${PROJECT_NAME}_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/cmake_pch.c
        ${${PROJECT_NAME}_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/cmake_pch.cxx
    )

    target_sources( ${PROJECT_NAME}
        PUBLIC
            ${${PROJECT_NAME}_sources}
        PRIVATE
            ${vendor_sources}
            ${resource_sources}
    )

    target_precompile_headers( ${PROJECT_NAME}
        PRIVATE
            ${root_list_dir}/src/pch.h
    )

    target_link_libraries( ${PROJECT_NAME}
        PRIVATE
            spdlog
    )

    if( MSVC )
        set_source_files_properties( ${vendor_sources} PROPERTIES COMPILE_OPTIONS "/w;/analyze-;" )
        set_source_files_properties( ${pch_sources} PROPERTIES COMPILE_OPTIONS "/w;$<$<CONFIG:Debug>:$<IF:$<BOOL:${RUN_CLANG_TIDY}>,/analyze,/analyze->;/WX-;>$<$<CONFIG:Release>:/analyze-;/WX;>" )
        set_source_files_properties( ${${PROJECT_NAME}_sources} PROPERTIES COMPILE_OPTIONS "/W4;/wd4652;/wd4100;/wd4996;/wd4206;$<$<CONFIG:Debug>:$<IF:$<BOOL:${RUN_CLANG_TIDY}>,/analyze,/analyze->;/WX-;>$<$<CONFIG:Release>:/analyze-;/WX;>" )
    else()
        set_source_files_properties( ${pch_sources} ${vendor_sources} PROPERTIES COMPILE_OPTIONS "-w;" )
        set_source_files_properties( ${${PROJECT_NAME}_sources} PROPERTIES COMPILE_OPTIONS "-Wall;-Werror;" )
    endif()

    install( PROGRAMS $<TARGET_FILE:${PROJECT_NAME}> DESTINATION ${PROJECT_NAME} )

endfunction()

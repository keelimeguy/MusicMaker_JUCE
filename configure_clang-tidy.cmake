cmake_minimum_required( VERSION 3.17.2 )

find_program( CLANG_TIDY_COMMAND NAMES clang-tidy )

if( EXISTS "${CMAKE_CURRENT_LIST_DIR}/.clang-tidy" )
    file( SHA1 ${CMAKE_CURRENT_LIST_DIR}/.clang-tidy clang_tidy_sha1 )
    set( CLANG_TIDY_DEFINITIONS "CLANG_TIDY_SHA1=${clang_tidy_sha1}" )
    unset( clang_tidy_sha1 )

    configure_file( ${CMAKE_CURRENT_LIST_DIR}/.clang-tidy .clang-tidy COPYONLY )
endif()

function( apply_clang_tidy_to_project project_name )

    if( NOT CLANG_TIDY_COMMAND )
        message( WARNING "RUN_CLANG_TIDY is ON but clang-tidy command is not found!" )

    else()

        if( MSVC )
            set_target_properties( ${project_name} PROPERTIES
                VS_GLOBAL_RunCodeAnalysis true
                VS_GLOBAL_ClangTidyToolExe "${CLANG_TIDY_COMMAND}"
                VS_GLOBAL_EnableClangTidyCodeAnalysis true
                # VS_GLOBAL_ClangTidyChecks ""
            )
            target_compile_options( ${PROJECT_NAME} PUBLIC "/analyze" )
        else()
            set_target_properties( ${project_name} PROPERTIES
                CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}"
            )
        endif()

        # Trigger complete recompile whenever ".clang-tidy" config file changes
        if( EXISTS "${CMAKE_CURRENT_LIST_DIR}/.clang-tidy" )
            target_compile_definitions( ${project_name} PUBLIC ${CLANG_TIDY_DEFINITIONS} )
        endif()

    endif()

endfunction()

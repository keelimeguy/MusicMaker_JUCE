cmake_minimum_required( VERSION 3.17.2 )

project( spdlog )

if( NOT ${${PROJECT_NAME}_LIBRARY_RELEASE} STREQUAL "${PROJECT_NAME}_LIBRARY_RELEASE-NOTFOUND" )
    add_library( ${PROJECT_NAME} INTERFACE )
    target_include_directories( ${PROJECT_NAME}
        INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bin/include
    )

    get_filename_component( ITEM_PATH ${${PROJECT_NAME}_LIBRARY_RELEASE} DIRECTORY )
    get_filename_component( ITEM_NAME ${${PROJECT_NAME}_LIBRARY_RELEASE} NAME )

    target_link_libraries( ${PROJECT_NAME}
        INTERFACE ${${PROJECT_NAME}_LIBRARY_RELEASE}
    )

else()
    execute_process( COMMAND git submodule update --init ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

    add_subdirectory( ${PROJECT_NAME} EXCLUDE_FROM_ALL )

    file( MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin )
    file( COPY ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}/include DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin/ )

    add_custom_command( OUTPUT ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_CURRENT_LIST_DIR}/bin/
        COMMAND touch ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
        DEPENDS ${PROJECT_NAME}
    )
    add_custom_target( ${PROJECT_NAME}_copy_files ALL
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
    )

endif()

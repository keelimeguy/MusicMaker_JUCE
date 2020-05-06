cmake_minimum_required( VERSION 3.17.2 )


####################################################################
# Create project
####################################################################

project( main VERSION 0.0.1 LANGUAGES CXX )

add_executable( ${PROJECT_NAME} )


####################################################################
# Add project sources
####################################################################

set( HEADER_FILES
)

set( SRC_FILES
    src/main.cpp
)

source_group( TREE ${CMAKE_CURRENT_LIST_DIR}/include PREFIX "Header Files"
    FILES ${HEADER_FILES}
)

source_group( TREE ${CMAKE_CURRENT_LIST_DIR}/src PREFIX "Source Files"
    FILES ${SRC_FILES}
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources( ${PROJECT_NAME}
    PRIVATE
        ${HEADER_FILES}
        ${SRC_FILES}
)


####################################################################
# Configure build
####################################################################

if( NOT WINDOWS_VS )
    target_compile_options( ${PROJECT_NAME}
        PRIVATE
            -Wall -Wextra -Wpedantic -Werror
    )

else()
    target_compile_options( ${PROJECT_NAME}
        PRIVATE
            -W4 -WX
    )

endif()

####################################################################
# Additional properties
####################################################################

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
        DEBUG_POSTFIX "_debug"
)

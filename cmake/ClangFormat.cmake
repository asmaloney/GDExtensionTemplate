# SPDX-License-Identifier: Unlicense

find_program( CLANG_FORMAT_PROGRAM NAMES clang-format )

if ( CLANG_FORMAT_PROGRAM )
    message( STATUS "Using clang-format: ${CLANG_FORMAT_PROGRAM}" )

    get_target_property( _sources ${PROJECT_NAME} SOURCES )

    # Remove some files from the list
    list( FILTER _sources EXCLUDE REGEX ".*/extern/.*" )
    list( FILTER _sources EXCLUDE REGEX ".*/gen/.*" )
    list( FILTER _sources EXCLUDE REGEX ".*/*.gdextension.in" )
    list( FILTER _sources EXCLUDE REGEX ".*/Version.h.in" )

    add_custom_target( clang-format
        COMMAND "${CLANG_FORMAT_PROGRAM}" --style=file -i ${_sources}
        COMMENT "Running clang-format..."
        COMMAND_EXPAND_LISTS
        VERBATIM
    )
endif()

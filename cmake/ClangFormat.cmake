# SPDX-License-Identifier: Unlicense

find_program( ${PROJECT_NAME}_CLANG_FORMAT_EXE NAMES clang-format )

if ( ${PROJECT_NAME}_CLANG_FORMAT_EXE )
    get_target_property( _sources ${PROJECT_NAME} SOURCES )

    # Remove some files from the list
    list( FILTER _sources EXCLUDE REGEX ".*/extern/.*" )
    list( FILTER _sources EXCLUDE REGEX ".*/*.gdextension.in" )

    add_custom_target( clang-format
        COMMAND clang-format --style=file -i ${_sources}
        COMMENT "Running clang-format..."
        COMMAND_EXPAND_LISTS
        VERBATIM
    )
endif()

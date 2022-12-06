# SPDX-License-Identifier: Unlicense

cmake_minimum_required( VERSION 3.22 )

project( GDExtensionTemplate
    LANGUAGES
        CXX
    VERSION
        0.1.0
)

# Require out-of-source builds
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )

if ( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "[${PROJECT_NAME}] You cannot build in the source directory. Please use a build subdirectory." )
endif()

# Add paths to modules
list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/" )

# Add our gdextension template file to a source group for better display in IDEs
set( GD_EXTENSION_FILE_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/templates/template.gdextension.in )
source_group( "Extra Files" ${GD_EXTENSION_FILE_INPUT} )

# Generate our project's .gdextension file from the template
set( GD_EXTENSION_FILE ${PROJECT_NAME}.gdextension )
configure_file( ${GD_EXTENSION_FILE_INPUT} ${PROJECT_NAME}/${GD_EXTENSION_FILE} )

# Create our library
add_library( ${PROJECT_NAME} SHARED ${GD_EXTENSION_FILE_INPUT} )

target_compile_features( ${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

# OUTPUT_DIR is where we put the resulting library (in the build directory)
set( OUTPUT_DIR "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/" )

# LIB_DIR is where the actual library ends up. This is used in both the build directory and the
# install directory and needs to be consistent with the paths in the gdextension file.
#   e.g. macos.release.x86_64 = "lib/Darwin-x86_64/libGDExtensionTemplate.dylib"
set( LIB_DIR "lib/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}" )

message( "Building ${PROJECT_NAME} for ${CMAKE_SYSTEM_NAME} on ${CMAKE_SYSTEM_PROCESSOR}")

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN true
        DEBUG_POSTFIX "-d"
        POSITION_INDEPENDENT_CODE ON
        RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/${LIB_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}/${LIB_DIR}"
)

add_subdirectory( src )

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "${PROJECT_BINARY_DIR}/src"
)

# Install library and extension file in ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
install( TARGETS ${PROJECT_NAME}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/${LIB_DIR}
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/${LIB_DIR}
)

install(
    FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${GD_EXTENSION_FILE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
)

# godot-cpp
# From here: https://github.com/godotengine/godot-cpp
if ( NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/extern/godot-cpp/Makefile" )
    message(
        FATAL_ERROR
            "[${PROJECT_NAME}] The godot-cpp submodule was not downloaded. Please update submodules: git submodule update --init --recursive."
    )
endif()

add_subdirectory( extern/godot-cpp )

set_target_properties( godot-cpp
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${GODOT_HEADERS_DIR}
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        godot-cpp
)

# ccache
# https://crascit.com/2016/04/09/using-ccache-with-cmake/
find_program( CCACHE_PROGRAM ccache )

if ( CCACHE_PROGRAM )
    set_target_properties( ${PROJECT_NAME}
        PROPERTIES
            CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}"
            C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}"
        )
endif()

# Formatting
# Adds a custom target to format all the code at once
include( ClangFormat )

# SPDX-License-Identifier: Unlicense

cmake_minimum_required( VERSION 3.22 )

# Build universal lib on macOS
if ( APPLE )
    set( CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" )
endif()

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

# Turn on link time optimization for everything
set( CMAKE_INTERPROCEDURAL_OPTIMIZATION ON )

# Get our gdextension input file name based on build type
string( TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE )
set( GD_EXTENSION_FILE_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/templates/template.${BUILD_TYPE}.gdextension.in )

# Add our gdextension template file to a source group for better display in IDEs
source_group( "Extra Files" "${GD_EXTENSION_FILE_INPUT}" )

# Generate our project's .gdextension file from the template
set( GD_EXTENSION_FILE ${PROJECT_NAME}.gdextension )
configure_file( ${GD_EXTENSION_FILE_INPUT} ${PROJECT_NAME}/${GD_EXTENSION_FILE} )

# Create our library
add_library( ${PROJECT_NAME} SHARED ${GD_EXTENSION_FILE_INPUT} )

target_compile_features( ${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

# LIB_ARCH is the architecture being built. It is set to the build system's architecture.
# For macOS, we build a universal library (both arm64 and x86_64).
set( LIB_ARCH ${CMAKE_SYSTEM_PROCESSOR} )
if ( APPLE )
    set( LIB_ARCH "universal" )
endif()

# LIB_DIR is where the actual library ends up. This is used in both the build directory and the
# install directory and needs to be consistent with the paths in the gdextension file.
#   e.g. linux.release.x86_64 = "lib/Linux-x86_64/libGDExtensionTemplate.so"
set( LIB_DIR "lib/${CMAKE_SYSTEM_NAME}-${LIB_ARCH}" )

message( STATUS "Building ${PROJECT_NAME} for ${LIB_ARCH} on ${CMAKE_SYSTEM_NAME}")

# BUILD_OUTPUT_DIR is where we put the resulting library (in the build directory)
set( BUILD_OUTPUT_DIR "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/" )

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN true
        DEBUG_POSTFIX "-d"
        RUNTIME_OUTPUT_DIRECTORY "${BUILD_OUTPUT_DIR}/${LIB_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${BUILD_OUTPUT_DIR}/${LIB_DIR}"
)

add_subdirectory( src )

# Install library and extension file in ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
set( INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/" )

message( STATUS "Install directory: ${INSTALL_DIR}")

install( TARGETS ${PROJECT_NAME}
    LIBRARY
        DESTINATION ${INSTALL_DIR}/${LIB_DIR}
    RUNTIME
        DESTINATION ${INSTALL_DIR}/${LIB_DIR}
)

# Install the gdextension file from the build directory
install(
    FILES ${BUILD_OUTPUT_DIR}/${GD_EXTENSION_FILE}
    DESTINATION ${INSTALL_DIR}
)

# ccache
# Turns on ccache if found
include( ccache )

# Formatting
# Adds a custom target to format all the code at once
include( ClangFormat )

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
        CXX_VISIBILITY_PRESET hidden    # visibility needs to be the same as the main library
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        godot-cpp
)

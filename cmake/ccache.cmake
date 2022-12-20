# SPDX-License-Identifier: Unlicense

# See: https://crascit.com/2016/04/09/using-ccache-with-cmake/
find_program( CCACHE_PROGRAM ccache )

if ( CCACHE_PROGRAM )
    message( STATUS "Using ccache: ${CCACHE_PROGRAM}" )

    # Turn on ccache for all targets
    set( CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}" )
    set( CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}" )
endif()

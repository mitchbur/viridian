cmake_minimum_required (VERSION 3.11)

project ( libviridian )

add_definitions ( -std=c++14 )

add_library( viridian
	viridian.h
	viridian.cpp )

# The version number.
set ( viridian_VERSION_MAJOR 0 )
set ( viridian_VERSION_MINOR 1 )

# configure the header file containing version information
configure_file (
	"${PROJECT_SOURCE_DIR}/viridian_config.h.in"
	"${PROJECT_BINARY_DIR}/viridian_config.h"
 )
# add the binary tree to the search path for include files
include_directories ( "${PROJECT_BINARY_DIR}" )

install ( TARGETS viridian DESTINATION lib )
install ( FILES viridian.h DESTINATION include )
install ( FILES "${PROJECT_BINARY_DIR}/viridian_config.h" DESTINATION include )

add_subdirectory ( unittest )

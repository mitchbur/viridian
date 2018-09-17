cmake_minimum_required (VERSION 3.11)

project ( viridian )

# standard c++14
set ( CMAKE_CXX_STANDARD 14 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF )

add_library( ${PROJECT_NAME}
	viridian.h
	vectorpair.h
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

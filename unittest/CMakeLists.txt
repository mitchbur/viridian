project ( libviridian_unittest )

set ( EXTRA_LIBS ${EXTRA_LIBS} viridian )
include_directories ( "${PROJECT_SOURCE_DIR}/.." )

# google gtest library
set ( EXTRA_LIBS ${EXTRA_LIBS} gtest gtest_main )
if ( CMAKE_HOST_UNIX )
	include_directories ( "/usr/local/include" )
	link_directories ( "/usr/local/lib" )
elseif ( CMAKE_HOST_WIN32 )
	# where to look for googletest library and include files
endif ( CMAKE_HOST_UNIX )

add_executable ( libviridian_unittest
	utest_viridian.cpp
 )
target_link_libraries ( libviridian_unittest ${EXTRA_LIBS} )

project ( viridian_unittest )

set ( EXTRA_LIBS ${EXTRA_LIBS} viridian )
include_directories ( "${viridian_SOURCE_DIR}" )

# googletest library
set ( EXTRA_LIBS ${EXTRA_LIBS} gtest gtest_main )
if ( CMAKE_HOST_UNIX )
	include_directories ( "/usr/local/include" )
	link_directories ( "/usr/local/lib" )
elseif ( CMAKE_HOST_WIN32 )
	# Make packages.config file for Visual Studio build environment
	set( googletest_NUGET_ID_PREFIX "Microsoft.googletest" )
	set( googletest_NUGET_ID_SUFFIX "v140.windesktop.msvcstl.static.rt-dyn" )
	set( googletest_NUGET_ID "${googletest_NUGET_ID_PREFIX}.${googletest_NUGET_ID_SUFFIX}" )
	set( googletest_NUGET_VERSION "1.8.0" )
	set( googletest_NUGET_TARGET "native" )
	configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/packages.config.in
		${CMAKE_CURRENT_BINARY_DIR}/packages.config )

	# googletest include files and libraries
	set( VISUAL_PACKAGE_DIR "${CMAKE_BINARY_DIR}/packages" )
	set( VISUAL_MACRO_PLATFORMTARGET "$(PlatformTarget)" )
	set( googletest_PACKAGE_DIR "${VISUAL_PACKAGE_DIR}/${googletest_NUGET_ID}.${googletest_NUGET_VERSION}" )
	include_directories ( "${googletest_PACKAGE_DIR}/build/${googletest_NUGET_TARGET}/include" )
	string(REGEX REPLACE "\\." "/" googletest_LIB_SUFFIX_PATH ${googletest_NUGET_ID_SUFFIX} )
	link_directories ( "${googletest_PACKAGE_DIR}/lib/${googletest_NUGET_TARGET}/${googletest_LIB_SUFFIX_PATH}/${VISUAL_MACRO_PLATFORMTARGET}" )
endif ( CMAKE_HOST_UNIX )

add_executable ( ${PROJECT_NAME}
	test_viridian.cpp
	test_vectorpair.cpp
 )
target_link_libraries ( ${PROJECT_NAME} ${EXTRA_LIBS} )

if ( CMAKE_HOST_WIN32 )
	# pre-processor macro to prevent TR1 namespace deprecation warnings
	target_compile_definitions( ${PROJECT_NAME} PUBLIC _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING )
endif ( CMAKE_HOST_WIN32 )

#include "viridian.h"
#include <gtest/gtest.h>

TEST( viridian, version )
{
	int version_major = VIRIDIAN_VERSION_MAJOR;
	int version_minor = VIRIDIAN_VERSION_MINOR;
	
	EXPECT_EQ( version_major, 0 );
	EXPECT_GT( version_minor, 0 );
}

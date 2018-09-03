#include "viridian.h"
#include <gtest/gtest.h>
#include <algorithm>

TEST( header, version )
{
	int version_major = VIRIDIAN_VERSION_MAJOR;
	int version_minor = VIRIDIAN_VERSION_MINOR;
	
	EXPECT_EQ( version_major, 0 );
	EXPECT_GE( version_minor, 2 );
}

using TestClass = viridian::TagValueMapBase;

class TagValueMapBaseTest : public ::testing::Test
{
protected:
	TestClass tagvals_map;

	static const TestClass::key_type tag_lemon;
	static const TestClass::key_type tag_lemon_JP;
	static const TestClass::mapped_type val_lemon;
	static const TestClass::mapped_type val_lemon_2;
	static const TestClass::key_type tag_tangerine;
	static const TestClass::key_type tag_tangerine_JP;
	static const TestClass::mapped_type val_tangerine;
	static const TestClass::mapped_type val_tangerine_2;
};

// 🍋
// lemon
// Unicode: U+1F34B, UTF-8: F0 9F 8D 8B
const TestClass::key_type TagValueMapBaseTest::tag_lemon { u8"lemon" };
const TestClass::key_type TagValueMapBaseTest::tag_lemon_JP { u8"レモン" };
const TestClass::mapped_type TagValueMapBaseTest::val_lemon { u8"a lemon \U0001F34B" };
const TestClass::mapped_type TagValueMapBaseTest::val_lemon_2 { u8"a lemon 🍋" };
// 🍊
// tangerine
// Unicode: U+1F34A, UTF-8: F0 9F 8D 8A
const TestClass::key_type TagValueMapBaseTest::tag_tangerine { u8"tangerine" };
const TestClass::key_type TagValueMapBaseTest::tag_tangerine_JP { u8"タンジェリン" };
const TestClass::mapped_type TagValueMapBaseTest::val_tangerine { u8"a tangerine \U0001F34A" };
const TestClass::mapped_type TagValueMapBaseTest::val_tangerine_2 { u8"a tangerine 🍊" };

TEST_F( TagValueMapBaseTest, insert_one )
{
	// initial size is 0
	{
		auto map_size_after_create = tagvals_map.get_map().size();
		decltype( map_size_after_create ) expected_map_size = 0;
		ASSERT_EQ( map_size_after_create, expected_map_size );
	}

	// add one item to map
	tagvals_map[ tag_lemon_JP ] = val_lemon;

	// at this point there should be exactly one item in the map
	{
		auto map_size_after_insert = tagvals_map.get_map().size();
		decltype( map_size_after_insert ) expected_map_size = 1;
		ASSERT_EQ( map_size_after_insert, expected_map_size );
	}

	// check that key is in map and that mapped value is correct
	{
		auto lookup_key = tag_lemon_JP;
		auto expected_mapped_value = val_lemon;
		decltype( tagvals_map)::mapped_type val_at;

		ASSERT_NO_THROW(
			val_at = tagvals_map.get_map().at( lookup_key );
		) << "expected key '" << lookup_key << "' was not found in map";
		ASSERT_EQ( val_at, expected_mapped_value );
	}
}

TEST_F( TagValueMapBaseTest, insert_default )
{
	// initial size is 0
	{
		auto map_size_after_create = tagvals_map.get_map().size();
		decltype( map_size_after_create ) expected_map_size = 0;
		EXPECT_EQ( map_size_after_create, expected_map_size );
	}
	
	// add one item to map
	auto map_item_x = tagvals_map[ tag_tangerine ];
	
	// at this point there should be exactly one item in the map
	{
		auto map_size_after_insert = tagvals_map.get_map().size();
		decltype( map_size_after_insert ) expected_map_size = 1;
		EXPECT_EQ( map_size_after_insert, expected_map_size );
	}
	
	// check that key is in map and that mapped value is correct
	{
		auto lookup_key = tag_tangerine;
		decltype( tagvals_map )::mapped_type expected_mapped_value { };
		decltype( tagvals_map )::mapped_type val_at;
		
		ASSERT_NO_THROW(
						val_at = tagvals_map.get_map().at( lookup_key );
						) << "expected key '" << lookup_key << "' was not found in map";
		ASSERT_EQ( val_at, expected_mapped_value );
	}
}

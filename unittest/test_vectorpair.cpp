//
//  unittest_vectorpair.cpp
//  viridian
//
//  Created by Mitch Burghart on 2018/09/16.
//
#include "viridian.h"
#include <gtest/gtest.h>

using namespace viridian;

class Test_vectorpair_iterator: public ::testing::Test {
protected:
  using vp_test_type = vectorpair<float, std::string>;
  vp_test_type blue_vpair;
  static const float blue_expected_f_values[5];
  static const std::string blue_expected_s_values[5];
  static constexpr std::size_t blue_expected_size =
    std::cend(blue_expected_f_values) - std::cbegin( blue_expected_f_values);
  
  void SetUp() override {
    for ( int k = 0; k < blue_expected_size; ++k )
    {
      blue_vpair.push_back( std::make_tuple( blue_expected_f_values[k], blue_expected_s_values[k] ) );
    }
  }
  
  void TearDown( ) override
  {
    
  }
};
const float Test_vectorpair_iterator::blue_expected_f_values[] = {
  3.14F, 1962.0911F, 1961.1110F, -13.125F, 0.0F
};
const std::string Test_vectorpair_iterator::blue_expected_s_values[] = {
  u8"trois",
  u8"soixante-et-deux",
  u8"soixante-et-un",
  u8"moins treize",
  u8"zero"
};

TEST( Test_vectorpair, one_row )
{
  using vp_test_type = vectorpair<double, int>;
  vp_test_type vpair {};

  double d_expected = 1.2E3;
  int i_expected = -3;
  vpair.push_back( std::make_tuple( d_expected,i_expected));
  
  const auto row = vpair[ 0 ];
  double d_obs = std::get<0>(row);
  int i_obs = std::get<1>(row);

  EXPECT_EQ( d_obs, d_expected );
  EXPECT_EQ( i_obs, i_expected );
}

TEST( Test_vectorpair, row_ref )
{
  using vp_test_type = vectorpair<float, unsigned>;
  vp_test_type vpair {};
  
  float f_expected_0 = 3.1415926F;
  unsigned u_expected_0 = 11;
  vpair.push_back( std::make_tuple( f_expected_0, u_expected_0 ) );

  float f_expected_1 = -6.54;
  unsigned u_expected_1 = 61;
  vpair.push_back( std::make_tuple( f_expected_1, u_expected_1 ) );

  float f_obs;
  unsigned u_obs;
  std::tie( f_obs, u_obs ) = vpair[0];
  EXPECT_EQ( f_obs, f_expected_0 );
  EXPECT_EQ( u_obs, u_expected_0 );
  std::tie( f_obs, u_obs ) = vpair[1];
  EXPECT_EQ( f_obs, f_expected_1 );
  EXPECT_EQ( u_obs, u_expected_1 );

  float f_expected_0b = -11.5F;
  unsigned u_expected_0b = 4;
  vpair[0] = std::make_tuple( f_expected_0b, u_expected_0b );
  
  const auto obs_newval_row_0 = vpair[0];
  EXPECT_EQ( std::get<0>(obs_newval_row_0), f_expected_0b );
  EXPECT_EQ( std::get<1>(obs_newval_row_0), u_expected_0b );
  
  const auto obs_newval_row_1 = vpair[1];
  EXPECT_EQ( std::get<0>(obs_newval_row_1), f_expected_1 );
  EXPECT_EQ( std::get<1>(obs_newval_row_1), u_expected_1 );
}

TEST_F( Test_vectorpair_iterator, input_iterator_neq )
{
  auto begin_iter = blue_vpair.begin();
  auto end_iter = blue_vpair.end();
  EXPECT_TRUE( begin_iter != end_iter );
  
  auto second_begin_iter = blue_vpair.begin();
  EXPECT_TRUE( begin_iter == second_begin_iter );
  EXPECT_TRUE( end_iter != second_begin_iter );

  auto second_end_iter = blue_vpair.end();
  EXPECT_TRUE( end_iter == second_end_iter );
  EXPECT_TRUE( begin_iter != second_end_iter );
  EXPECT_TRUE( second_begin_iter != second_end_iter );
}

TEST_F( Test_vectorpair_iterator, input_iterator_deref )
{
  auto begin_iter = blue_vpair.begin();
  auto obs_row = *begin_iter;
  EXPECT_EQ( std::get<0>(obs_row), blue_expected_f_values[0] );
  EXPECT_EQ( std::get<1>(obs_row), blue_expected_s_values[0] );
}

TEST_F( Test_vectorpair_iterator, input_iterator_preincr )
{
  auto iter = blue_vpair.begin();
  for ( int k = 1; k < blue_expected_size; ++k )
  {
    auto incr_iter = ++iter;
    // both the return value and iter should point to element k
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k] );
    auto obs_incr_iter_row = *incr_iter;
    EXPECT_EQ( std::get<0>(obs_incr_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_incr_iter_row), blue_expected_s_values[k] );
  }
}

TEST_F( Test_vectorpair_iterator, forward_iterator_postincr )
{
  auto iter = blue_vpair.begin();

  iter++;
  auto obs_iter_row = *iter;
  EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[1] );
  EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[1] );
}

TEST_F( Test_vectorpair_iterator, forward_iterator_deref_postincr )
{
  auto iter = blue_vpair.begin();

  for ( int k = 0; k < blue_expected_size-1; ++k )
  {
    // return value should be element k
    // iter should point to element k+1
    auto obs_postincr_row = *iter++;
    EXPECT_EQ( std::get<0>(obs_postincr_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_postincr_row), blue_expected_s_values[k] );
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k+1] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k+1] );
  }
}

TEST_F( Test_vectorpair_iterator, bidirectional_iterator_predecr )
{
  auto iter = blue_vpair.end();
  // decrement from end expecting elements in range [ N-1 .. 0 ]
  for ( int k = blue_expected_size-1; k >= 0; --k )
  {
    auto decr_iter = --iter;
    // both the return value and iter should point to element k
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k] );
    auto obs_decr_iter_row = *decr_iter;
    EXPECT_EQ( std::get<0>(obs_decr_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_decr_iter_row), blue_expected_s_values[k] );
  }
}

TEST_F( Test_vectorpair_iterator, bidirectional_iterator_postdecr )
{
  auto iter = blue_vpair.end();
  for ( int k = blue_expected_size - 1; k >= 0; --k )
  {
    iter--;
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k] );
  }
}

TEST_F( Test_vectorpair_iterator, bidirectional_iterator_deref_postdecr )
{
  auto iter = blue_vpair.end();
  --iter;
  
  for ( int k = blue_expected_size-1; k > 0; --k )
  {
    // return value should be element k
    // iter should point to element k-1
    auto obs_postdecr_row = *iter--;
    EXPECT_EQ( std::get<0>(obs_postdecr_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_postdecr_row), blue_expected_s_values[k] );
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k-1] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k-1] );
  }
}

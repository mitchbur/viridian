//
//  unittest_vectorpair.cpp
//  viridian
//
//  Created by Mitch Burghart on 2018/09/16.
//
#include "viridian.h"
#include <gtest/gtest.h>

TEST( vectorpair, one_row )
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

TEST( vectorpair, row_ref )
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

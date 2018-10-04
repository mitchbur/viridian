//
//  unittest_vectorpair_const_iterator.cpp
//  viridian
//
//  Created by Mitch Burghart on 2018/10/04.
//
#include "viridian.h"
#include <gtest/gtest.h>

using namespace viridian;

class Test_vectorpair_const_iterator: public ::testing::Test {
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
const float Test_vectorpair_const_iterator::blue_expected_f_values[] = {
  3.14F, 1962.0911F, 1961.1110F, -13.125F, 0.0F
};
const std::string Test_vectorpair_const_iterator::blue_expected_s_values[] = {
  u8"trois",
  u8"soixante-et-deux",
  u8"soixante-et-un",
  u8"moins treize",
  u8"zero"
};

TEST_F( Test_vectorpair_const_iterator, copy_constructor )
{
  using iter_type = vp_test_type::const_iterator;
  iter_type an_iter = blue_vpair.cbegin();
  iter_type constructed_copy { an_iter };
  EXPECT_EQ( an_iter, constructed_copy );
  iter_type incremented_constructed_copy { ++constructed_copy };
  EXPECT_NE( an_iter, incremented_constructed_copy );
}

TEST_F( Test_vectorpair_const_iterator, copy_assignment )
{
  using iter_type = vp_test_type::const_iterator;
  iter_type an_iter = blue_vpair.cbegin();
  iter_type iter_copy;
  iter_copy = an_iter;
  EXPECT_EQ( an_iter, iter_copy );
  iter_type incremented_iter_copy { ++iter_copy };
  EXPECT_NE( an_iter, incremented_iter_copy );
}

TEST_F( Test_vectorpair_const_iterator, input_iterator_neq )
{
  auto begin_iter = blue_vpair.cbegin();
  auto end_iter = blue_vpair.cend();
  EXPECT_TRUE( begin_iter != end_iter );
  
  auto second_begin_iter = blue_vpair.cbegin();
  EXPECT_TRUE( begin_iter == second_begin_iter );
  EXPECT_TRUE( end_iter != second_begin_iter );
  
  auto second_end_iter = blue_vpair.cend();
  EXPECT_TRUE( end_iter == second_end_iter );
  EXPECT_TRUE( begin_iter != second_end_iter );
  EXPECT_TRUE( second_begin_iter != second_end_iter );
}

TEST_F( Test_vectorpair_const_iterator, input_iterator_deref )
{
  auto begin_iter = blue_vpair.cbegin();
  auto obs_row = *begin_iter;
  EXPECT_EQ( std::get<0>(obs_row), blue_expected_f_values[0] );
  EXPECT_EQ( std::get<1>(obs_row), blue_expected_s_values[0] );
}

TEST_F( Test_vectorpair_const_iterator, input_iterator_preincr )
{
  auto iter = blue_vpair.cbegin();
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

TEST_F( Test_vectorpair_const_iterator, forward_iterator_postincr )
{
  auto iter = cbegin( blue_vpair );
  
  iter++;
  auto obs_iter_row = *iter;
  EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[1] );
  EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[1] );
}

TEST_F( Test_vectorpair_const_iterator, forward_iterator_deref_postincr )
{
  auto iter = blue_vpair.cbegin();
  
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

TEST_F( Test_vectorpair_const_iterator, bidirectional_iterator_predecr )
{
  auto iter = blue_vpair.cend();
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

TEST_F( Test_vectorpair_const_iterator, bidirectional_iterator_postdecr )
{
  auto iter = blue_vpair.cend();
  for ( int k = blue_expected_size - 1; k >= 0; --k )
  {
    iter--;
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k] );
  }
}

TEST_F( Test_vectorpair_const_iterator, bidirectional_iterator_deref_postdecr )
{
  auto iter = blue_vpair.cend();
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

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_pluseq_zero )
{
  auto iter = blue_vpair.cbegin();
  iter += 0;
  auto obs_iter_row = *iter;
  EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[0] );
  EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[0] );
}

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_pluseq_one )
{
  auto iter = blue_vpair.cbegin();
  for ( int k = 0; k < blue_expected_size; ++k )
  {
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k] );
    iter += 1;
  }
}

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_pluseq_two )
{
  auto iter = blue_vpair.cbegin();
  for ( int k = 0; k < blue_expected_size; k += 2 )
  {
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k] );
    iter += 2;
  }
}

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_add )
{
  auto iter = blue_vpair.cbegin();
  constexpr int step = 2;
  for ( int k = step; k < blue_expected_size; k += step )
  {
    auto advanced_iter = iter + step;
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k-step] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k-step] );
    auto obs_advanced_iter_row = *advanced_iter;
    EXPECT_EQ( std::get<0>(obs_advanced_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_advanced_iter_row), blue_expected_s_values[k] );
    
    iter += step;
  }
}

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_commutated_add )
{
  auto iter = blue_vpair.cbegin();
  int step = 2;
  for ( int k = step; k < blue_expected_size; k += step )
  {
    auto advanced_iter = step + iter;
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k-step] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k-step] );
    auto obs_advanced_iter_row = *advanced_iter;
    EXPECT_EQ( std::get<0>(obs_advanced_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_advanced_iter_row), blue_expected_s_values[k] );
    
    iter += step;
  }
}

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_minuseq_zero )
{
  auto iter = blue_vpair.cbegin();
  ++iter;
  
  iter -= 0;
  auto obs_iter_row = *iter;
  EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[1] );
  EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[1] );
}

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_minuseq_one )
{
  auto iter = blue_vpair.cend();
  --iter;
  
  for ( int k = blue_expected_size-1; k >= 0; --k )
  {
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k] );
    iter -= 1;
  }
}

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_minuseq_two )
{
  constexpr int step = 2;
  auto iter = blue_vpair.cend();
  --iter;  // point to last element in vector
  
  for ( int k = blue_expected_size-1; k >= 0; k -= step )
  {
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k] );
    iter -= step;
  }
}

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_subtract )
{
  auto iter = blue_vpair.cend();
  --iter;  // point to last element in vector
  
  constexpr int step = 2;
  for ( int k = blue_expected_size - 1; k >= step; k -= step )
  {
    auto decremented_iter = iter - step;
    auto obs_iter_row = *iter;
    EXPECT_EQ( std::get<0>(obs_iter_row), blue_expected_f_values[k] );
    EXPECT_EQ( std::get<1>(obs_iter_row), blue_expected_s_values[k] );
    auto obs_decremented_iter_row = *decremented_iter;
    EXPECT_EQ( std::get<0>(obs_decremented_iter_row), blue_expected_f_values[k-step] );
    EXPECT_EQ( std::get<1>(obs_decremented_iter_row), blue_expected_s_values[k-step] );
    
    iter -= step;
  }
}

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_difference )
{
  auto low_iter = blue_vpair.cbegin();
  auto high_iter = blue_vpair.cend();
  vp_test_type::iterator::difference_type diff;
  
  // check differences as low_iter is increased
  for ( vp_test_type::iterator::difference_type expected_diff = blue_expected_size;
       expected_diff <= 0; --expected_diff )
  {
    diff = high_iter - low_iter;
    EXPECT_EQ( diff, expected_diff );
    
    ++low_iter;
  }
}

TEST_F( Test_vectorpair_const_iterator, random_access_iterator_difference_b )
{
  auto low_iter = blue_vpair.cbegin();
  auto high_iter = blue_vpair.cend();
  vp_test_type::iterator::difference_type diff;
  
  // check differences as high_iter is decreased
  for ( vp_test_type::iterator::difference_type expected_diff = blue_expected_size;
       expected_diff <= 0; --expected_diff )
  {
    diff = high_iter - low_iter;
    EXPECT_EQ( diff, expected_diff );
    
    --high_iter;
  }
}

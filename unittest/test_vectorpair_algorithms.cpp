//
//  unittest_vectorpair_algorithms.cpp
//  viridian
//
//  Created by Mitch Burghart on 2018/10/07.
//
#include "viridian.h"
#include <gtest/gtest.h>

using namespace viridian;

class Test_vectorpair_algorithms: public ::testing::Test {
protected:
  using vp5_test_type = vectorpair<float, std::string>;
  vp5_test_type size5_vpair;
  static constexpr std::size_t size5_expected_size = 5;
  static const float size5_expected_f_values[size5_expected_size];
  static const std::string size5_expected_s_values[size5_expected_size];
  static const int size5_expected_f_order[size5_expected_size];
  static const int size5_expected_s_order[size5_expected_size];

  using vp130_test_type = vectorpair<int, float>;
  vp130_test_type size130_vpair;
  static constexpr std::size_t size130_expected_size = 130;
  static const int size130_expected_i_values[size130_expected_size];
  static const int size130_expected_i_order[size130_expected_size];
  static const float size130_expected_f_values[size130_expected_size];
  static const int size130_expected_f_order[size130_expected_size];

  void SetUp() override {
    for ( int k = 0; k < size5_expected_size; ++k )
    {
      size5_vpair.push_back( std::make_tuple( size5_expected_f_values[k], size5_expected_s_values[k] ) );
    }
    for ( int k = 0; k < size130_expected_size; ++k )
    {
      size130_vpair.push_back( std::make_tuple( size130_expected_i_values[k], size130_expected_f_values[k] ) );
    }
  }
  
  void TearDown( ) override
  {
    
  }
};
const float Test_vectorpair_algorithms::size5_expected_f_values[] = {
  3.14F, 1962.0911F, 1961.1110F, -13.125F, 0.0F
};
const int Test_vectorpair_algorithms::size5_expected_f_order[] = { 3, 4, 0, 2, 1 };
const std::string Test_vectorpair_algorithms::size5_expected_s_values[] = {
  u8"trois",
  u8"soixante-et-deux",
  u8"soixante-et-un",
  u8"moins treize",
  u8"zero"
};
const int Test_vectorpair_algorithms::size5_expected_s_order[] = { 3, 1, 2, 0, 4 };
const int Test_vectorpair_algorithms::size130_expected_i_values[] = {
  7933, 4097, 6774,  434, 6866, 4830, 4214, 4297, 1790, 5467, 6328, 2000, 3513, 6119, 5063,
  1909, 1333,  320, 4534,  929, 1706, 1536, 2055, 4969, 1042, 6801, 6545, 5619, 4262,  779,
  7626, 7196, 6230, 2321, 2370, 1643, 7550, 6413,  820,   78, 1051,  283, 2034, 2794, 5357,
  4937, 5794, 7828, 6587, 3299, 1104, 5155, 5165, 8096, 4029, 4887, 3540, 1612, 7486,  729,
  2457, 4009, 7192, 7768, 1451,  783, 5250, 5120, 6803, 1757, 3088, 2586, 7746,  598, 5579,
  4734, 4884, 7248, 2188,   63, 3845, 1449, 3313, 6661, 5744, 2231,  523, 2153, 7217, 4060,
  1033, 5326, 5683, 4118, 1509, 2186, 1286, 2353, 4595, 7984, 7495,  323, 1735, 7101, 3381,
  329, 1616, 4617, 4763, 1100, 7064, 4594, 3151, 6336, 5065, 4075, 4279, 2346, 1870, 3935,
  2774, 1393,   49, 1077,  772, 4463, 1494,  842, 6257, 7080
};
const int Test_vectorpair_algorithms::size130_expected_i_order[] = {
  122,  79,  39,  41,  17, 101, 105,   3,  86,  73,  59, 124,  29,  65,  38, 127,  19,  90,
  24,  40, 123, 109,  50,  96,  16, 121,  81,  64, 126,  94,  21,  57, 106,  35,  20, 102,
  69,   8, 118,  15,  11,  42,  22,  87,  95,  78,  85,  33, 117,  97,  34,  60,  71, 120,
  43,  70, 112,  49,  82, 104,  12,  56,  80, 119,  61,  54,  89, 115,   1,  93,   6,  28,
  116,   7, 125,  18, 111,  98, 107,  75, 108,   5,  76,  55,  45,  23,  14, 114,  67,  51,
  52,  66,  91,  44,   9,  74,  27,  92,  84,  46,  13,  32, 128,  10, 113,  37,  26,  48,
  83,   2,  25,  68,   4, 110, 129, 103,  62,  31,  88,  77,  58, 100,  36,  30,  72,  63,
  47,   0,  99,  53
};
const float Test_vectorpair_algorithms::size130_expected_f_values[] = {
  38.96875, -33.68750,  16.84375,  65.31250, -82.84375,  22.75000,  83.71875,
  -16.21875, -54.68750,  35.18750,  70.46875, -81.93750,  10.62500,  14.87500,
  79.00000,  65.21875, -27.65625,  -6.62500,   2.96875,   0.56250, -41.75000,
  -54.34375,  92.93750, -64.15625, -88.93750,  52.46875,  -1.78125,  -4.93750,
  -90.71875,  38.25000, -10.40625, -26.84375, -46.15625,  85.71875, -82.71875,
  86.15625,  23.53125,  42.34375, -29.06250,  26.03125, -56.56250, -63.84375,
  7.87500, -32.56250, -71.25000, -20.65625,  -6.90625,  -1.37500, -61.81250,
  67.96875, -59.31250,  56.03125, -21.21875,  14.46875, -66.37500,  54.75000,
  24.62500, -29.00000, -80.71875, -70.84375,  40.15625,  -9.59375,  41.18750,
  75.37500, -60.25000,  82.59375, -50.09375, -70.68750,   9.53125,  98.81250,
  -97.31250,  -1.00000, -33.28125, -92.28125,   1.43750, -80.65625, -98.68750,
  72.46875,  18.43750, -94.34375, -68.21875,  58.50000, -87.03125, -35.93750,
  28.90625,  69.31250, -55.78125,  55.93750,  96.56250,  84.50000,  81.96875,
  45.59375, -29.50000,   7.96875,  94.65625, -11.50000,   1.68750,  30.34375,
  -7.25000,  33.84375, -10.56250,  57.12500,  86.65625, -85.78125, -58.03125,
  38.12500,  49.34375, -26.00000, -86.34375, -50.68750, -38.21875,   1.65625,
  -2.75000,  98.96875,  64.90625,   8.62500, -80.40625, -30.46875,  23.03125,
  -10.43750, -48.21875, -42.31250,  79.43750,  -6.65625,  79.53125, -67.62500,
  -27.75000,  48.65625,  20.25000,   0.34375
};
const int Test_vectorpair_algorithms::size130_expected_f_order[] = {
  76,  70,  79,  73,  28,  24,  82, 108, 103,   4,  34,  11,  58,  75, 116,  44,  59,  67,
  80, 125,  54,  23,  41,  48,  64,  50, 104,  40,  86,   8,  21, 109,  66, 120,  32, 121,
  20, 110,  83,   1,  72,  43, 117,  92,  38,  57, 126,  16,  31, 107,  52,  45,   7,  95,
  100, 119,  30,  61,  98,  46, 123,  17,  27, 112,  26,  47,  71, 129,  19,  74, 111,  96,
  18,  42,  93, 115,  68,  12,  53,  13,   2,  78, 128,   5, 118,  36,  56,  39,  84,  97,
  99,   9, 105,  29,   0,  60,  62,  37,  91, 127, 106,  25,  55,  87,  51, 101,  81, 114,
  15,   3,  49,  85,  10,  77,  63,  14, 122, 124,  90,  65,   6,  89,  33,  35, 102,  22,
  94,  88,  69, 113
};

TEST_F( Test_vectorpair_algorithms, algo_sort_small_float )
{
  std::sort(
             size5_vpair.begin(), size5_vpair.end(),
             [] ( const auto& a, const auto& b ) {
               return std::get<0>( a ) < std::get<0>( b );
             }
             );

  bool all_f_values_equal =
  std::equal(
             size5_vpair.begin(), size5_vpair.end(),
             std::cbegin( size5_expected_f_order ),
             [] ( auto row, auto ordered_k ) {
               return std::get<0>(row) == size5_expected_f_values[ ordered_k ];
             }
             );
  EXPECT_TRUE( all_f_values_equal );

  bool all_s_values_equal =
  std::equal(
             size5_vpair.begin(), size5_vpair.end(),
             std::cbegin( size5_expected_f_order ),
             [] ( auto row, auto ordered_k ) {
               return std::get<1>(row) == size5_expected_s_values[ ordered_k ];
             }
             );
  EXPECT_TRUE( all_s_values_equal );
}

TEST_F( Test_vectorpair_algorithms, algo_sort_small_string )
{
  std::sort(
            size5_vpair.begin(), size5_vpair.end(),
            [] ( const auto& a, const auto& b ) {
              return std::get<1>( a ) < std::get<1>( b );
            }
            );
  
  bool all_f_values_equal =
  std::equal(
             size5_vpair.begin(), size5_vpair.end(),
             std::cbegin( size5_expected_s_order ),
             [] ( auto row, auto ordered_k ) {
               return std::get<0>(row) == size5_expected_f_values[ ordered_k ];
             }
             );
  EXPECT_TRUE( all_f_values_equal );
  
  bool all_s_values_equal =
  std::equal(
             size5_vpair.begin(), size5_vpair.end(),
             std::cbegin( size5_expected_s_order ),
             [] ( auto row, auto ordered_k ) {
               return std::get<1>(row) == size5_expected_s_values[ ordered_k ];
             }
             );
  EXPECT_TRUE( all_s_values_equal );
}

TEST_F( Test_vectorpair_algorithms, algo_sort_large_int )
{
  std::sort(
            size130_vpair.begin(), size130_vpair.end(),
            [] ( const auto& a, const auto& b ) {
              return std::get<0>( a ) < std::get<0>( b );
            }
            );
  
  bool all_i_values_equal =
  std::equal(
             size130_vpair.begin(), size130_vpair.end(),
             std::cbegin( size130_expected_i_order ),
             [] ( auto row, auto ordered_k ) {
               return std::get<0>(row) == size130_expected_i_values[ ordered_k ];
             }
             );
  EXPECT_TRUE( all_i_values_equal );
  
  bool all_f_values_equal =
  std::equal(
             size130_vpair.begin(), size130_vpair.end(),
             std::cbegin( size130_expected_i_order ),
             [] ( auto row, auto ordered_k ) {
               return std::get<1>(row) == size130_expected_f_values[ ordered_k ];
             }
             );
  EXPECT_TRUE( all_f_values_equal );
}

TEST_F( Test_vectorpair_algorithms, algo_sort_large_float )
{
  std::sort(
            size130_vpair.begin(), size130_vpair.end(),
            [] ( const auto& a, const auto& b ) {
              return std::get<1>( a ) < std::get<1>( b );
            }
            );
  
  bool all_i_values_equal =
  std::equal(
             size130_vpair.begin(), size130_vpair.end(),
             std::cbegin( size130_expected_f_order ),
             [] ( auto row, auto ordered_k ) {
               return std::get<0>(row) == size130_expected_i_values[ ordered_k ];
             }
             );
  EXPECT_TRUE( all_i_values_equal );
  
  bool all_f_values_equal =
  std::equal(
             size130_vpair.begin(), size130_vpair.end(),
             std::cbegin( size130_expected_f_order ),
             [] ( auto row, auto ordered_k ) {
               return std::get<1>(row) == size130_expected_f_values[ ordered_k ];
             }
             );
  EXPECT_TRUE( all_f_values_equal );
}

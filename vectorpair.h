//
//  vectorpair.h
//  viridian
//
//  Created by Mitch Burghart on 2018/09/16.
//

#ifndef vectorpair_h
#define vectorpair_h

#include <algorithm>
#include <tuple>
#include <vector>

template< typename _TA, typename _TB >
class vectorpair;

template< typename _TA, typename _TB >
class vectorpair
{
public:
  using row_type = std::tuple< _TA, _TB >;
  using ref_row_type = std::tuple< _TA&, _TB& >;
  std::vector< _TA > vector_a;
  std::vector< _TB > vector_b;
  
  std::size_t size( ) const
  {
    return std::min( vector_a.size(), vector_b.size() );
  }

  void push_back( row_type r )
  {
    std::size_t curr_size = this->size();
    if ( vector_a.size() < curr_size )
    {
      vector_a[curr_size-1] = std::get<0>(r);
    }
    else{
      vector_a.push_back( std::get<0>(r));
    }
    if ( vector_b.size() < curr_size )
    {
      vector_b[curr_size-1] = std::get<1>(r);
    }
    else{
      vector_b.push_back( std::get<1>(r));
    }
  }

  inline row_type operator[]( int k ) const
  {
    return std::make_tuple( vector_a[k], vector_b[k] );
  }
  
  inline ref_row_type operator[]( int k )
  {
    return std::tie( vector_a[k], vector_b[k] );
  }
};


#endif /* vectorpair_h */

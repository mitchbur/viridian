//! \file vectorpair.h
//! vector pair template class header file
//  Created by Mitch Burghart on 2018-09-16.
//

#ifndef vectorpair_h
#define vectorpair_h

#include "viridian.h"
#include <algorithm>
#include <tuple>
#include <vector>

namespace viridian {
  
  template< typename _TA, typename _TB >
  class vectorpair;
  
  template <typename _CT, typename _RT, typename _PT >
  class vectorpair_pointer;

  template< typename _TA, typename _TB >
  class vectorpair
  {
  public:
    using self_type = vectorpair;

    using value_type = std::tuple<_TA, _TB>;
    using reference = std::tuple<_TA&, _TB&>;
    using const_reference = std::tuple<const _TA&, const _TB&>;
    using pointer = std::tuple<_TA*, _TB*>;
    using const_pointer = std::tuple<const _TA*, const _TB*>;

    using iter_pointer = vectorpair_pointer<self_type, reference, pointer>;
    using iter_const_pointer =
      vectorpair_pointer<const self_type, const_reference, const_pointer>;
    using iterator = index_iterator<iter_pointer>;
    using const_iterator = index_iterator<iter_const_pointer>;

    std::vector< _TA > vector_a;
    std::vector< _TB > vector_b;
    
    std::size_t size( ) const
    {
      return std::min( vector_a.size(), vector_b.size() );
    }
    
    void push_back( value_type r )
    {
      auto curr_size = this->size();
      if ( vector_a.size() < curr_size )
      {
        vector_a[curr_size-1] = std::get<0>(r);
      }
      else
      {
        vector_a.push_back( std::get<0>(r));
      }
      if ( vector_b.size() < curr_size )
      {
        vector_b[curr_size-1] = std::get<1>(r);
      }
      else
      {
        vector_b.push_back( std::get<1>(r));
      }
    }
    
    inline const_reference operator[]( int k ) const
    {
      return std::tie( vector_a[k], vector_b[k] );
    }
    
    inline reference operator[]( int k )
    {
      return std::tie( vector_a[k], vector_b[k] );
    }
    
    inline iterator begin( ) noexcept
    {
      return iterator { iter_pointer { *this,0} };
    }

    inline const_iterator begin( ) const noexcept
    {
      return const_iterator{ iter_const_pointer{ *this, 0 } };
    }

    inline iterator end( ) noexcept
    {
      typename iterator::difference_type end_index = this->size();
      return iterator{ iter_pointer{ *this, end_index } };
    }
    
    inline const_iterator end( ) const noexcept
    {
      typename iterator::difference_type end_index = this->size();
      return const_iterator{ iter_const_pointer{ *this, end_index } };
    }
    
    inline const_iterator cbegin( ) const noexcept
    {
      return begin( );
    }
    
    inline const_iterator cend( ) const noexcept
    {
      return end( );
    }
  };

  template < typename _CT, typename _RT, typename _PT >
  class vectorpair_pointer
  {
  public:
    using self_type = vectorpair_pointer;
    using container_type = _CT;

    using value_type = typename _CT::value_type;
    using reference = _RT;
    using difference_type = std::ptrdiff_t;
    using pointer = _PT;

    vectorpair_pointer( )
    : p_container_( nullptr )
    , pos_( 0 )
    {}
    
    vectorpair_pointer( container_type& container, difference_type pos ) noexcept
    : p_container_( &container )
    , pos_( pos )
    {}
    
    ~vectorpair_pointer( ) = default;
    
    // default copy constructor and copy assignment operators
    // default move constructor and move assignment operators
    vectorpair_pointer ( const self_type& ) = default;
    self_type & operator= ( const self_type & ) = default;
    vectorpair_pointer ( self_type && ) = default;
    self_type &  operator= ( self_type && ) = default;
    
    inline difference_type operator-( const self_type& b ) const
    {
      return this->pos_ - b.pos_;
    }
 
    inline reference operator*( ) const
    {
      return (*p_container_)[pos_];
    }

    inline reference operator[]( int k ) const
    {
      return (*p_container_)[pos_+k];
    }
    
    inline self_type& operator+=( int k )
    {
      pos_ += k;
      return *this;
    }
    
  private:
    container_type* p_container_;
    difference_type pos_;
  };

} /* end namespace */

namespace std {
  template< class ... _T >
  inline void swap( std::tuple< _T& ... > u, std::tuple< _T& ... > v )
  {
    std::tuple< _T ... > orig_u = std::move( u );
    u = std::move( v );
    v = std::move( orig_u );
  }
}

#endif /* vectorpair_h */

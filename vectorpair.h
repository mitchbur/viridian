//! \file vectorpair.h
//! vector pair template class header file
//  Created by Mitch Burghart on 2018/09/16.
//

#ifndef vectorpair_h
#define vectorpair_h

#include <algorithm>
#include <tuple>
#include <vector>

namespace viridian {
  
  template< typename _TA, typename _TB >
  class vectorpair;
  
  template< typename _TA, typename _TB >
  class vectorpair_iterator_;
  
  template< typename _TA, typename _TB >
  class vectorpair
  {
  public:
    using row_type = std::tuple< _TA, _TB >;
    using reference_row_type = std::tuple< _TA&, _TB& >;
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
    
    inline reference_row_type operator[]( int k )
    {
      return std::tie( vector_a[k], vector_b[k] );
    }
    
    vectorpair_iterator_<_TA,_TB> begin() {
      return vectorpair_iterator_<_TA,_TB>{*this,0};
    }
  };
  
  template< typename _TA, typename _TB >
  class vectorpair_iterator_
  {
  public:
    using self_type = vectorpair_iterator_< _TA, _TB >;
    using container_type = vectorpair< _TA, _TB >;

    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename container_type::row_type;
    using difference_type = std::ptrdiff_t;
    using pointer = void;
    using reference = typename vectorpair<_TA,_TB>::reference_row_type;

  protected:
    container_type& container_;
    difference_type pos_;

  public:
    vectorpair_iterator_( ) = default;
    vectorpair_iterator_( container_type& c, difference_type i)
    : container_( c )
    , pos_(i){}
    
    // Get the data element at this position
    inline reference operator*() const
    {
      return container_[pos_];
    }
    
    // ??? pointer operator->() const;
    
    // Move position forward 1 place
    self_type& operator++();
    self_type operator++(int);
    
    // Move position backward 1 place
    self_type& operator--();
    self_type operator--(int);
    
    
    /*+*/  // Random access operations
    
    ptrdiff_t operator- (const self_type&) const;
    // how many positions apart are these iterators?
    
    self_type operator+ (ptrdiff_t k) const;
    // Get a new iterator k positions past this one.
    
    self_type operator- (ptrdiff_t k) const;
    // Get a new iterator k positions before this one.
    /*-*/
    // Comparison operators
    bool operator== (const self_type&) const;
    bool operator!= (const self_type&) const;/*+*/
    bool operator<  (const self_type&) const;
    bool operator<= (const self_type&) const;
    bool operator>  (const self_type&) const;
    bool operator>= (const self_type&) const;/*-*/
  private:
    /*...*/
  };
  
  
}

#endif /* vectorpair_h */

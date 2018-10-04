//! \file index_iterator.h
//! index iterator template class header file
//  Created by Mitch Burghart on 2018-09-29.
//

#ifndef index_iterator_h
#define index_iterator_h

#include <iterator>

namespace viridian {
  
  template< typename _CI >
  class index_iterator
  {
  public:
    using core_iterator = _CI;
    using iterator = index_iterator;
    
    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename core_iterator::value_type;
    using difference_type = typename core_iterator::difference_type;
    using reference = typename core_iterator::reference;
    using pointer = typename core_iterator::pointer;

  private:
    core_iterator core_;
    
  public:
    
    // constructor, default
    index_iterator( )
    : core_( )
    {}
    
    // destructor
    ~index_iterator( ) = default;
    
    // constructor, from core iterator
    index_iterator( core_iterator&& c )
    : core_( c )
    {}
    
    // default copy constructor and copy assignment operators
    index_iterator ( const index_iterator& ) = default;
    index_iterator & operator= ( const index_iterator & ) = default;
    
    // default move constructor and move assignment operators
    index_iterator ( index_iterator && ) = default;
    index_iterator &  operator= ( index_iterator && ) = default;
    
    // +--- input iterator
    // |
    // +--- forward iterator
    // |
    
    inline bool operator!= (const iterator& b) const
    {
      return ( this->core_ - b.core_ ) != 0;
    }
    
    inline bool operator== (const iterator& b) const
    {
      return ! ( (*this) != b );
    }
    
    inline reference operator*() const
    {
      return core_[0];
    }
    
    //! pre-increment operator
    inline iterator& operator++()
    {
      core_ += 1;
      return *this;
    }
    //! post-increment operator
    inline iterator operator++(int)
    {
      iterator before = *this;
      ++(*this);
      return before;
    }
    
    // +--- bidirectional iterator
    // |
    
    //! pre-decrement operator
    inline iterator& operator--()
    {
      core_ += -1;
      return *this;
    }
    //! post-decrement operator
    inline iterator operator--(int)
    {
      iterator before = *this;
      --(*this);
      return before;
    }
    
    // +--- random access iterator
    // |
    
    inline iterator& operator+= (difference_type k)
    {
      core_ += k;
      return *this;
    }
    
    inline iterator operator+ (difference_type k) const
    {
      iterator b = *this;
      b += k;
      return b;
    }
    
    inline iterator& operator-= (difference_type k)
    {
      core_ += -k;
      return *this;
    }
    
    inline iterator operator- (difference_type k) const
    {
      iterator b = *this;
      b -= k;
      return b;
    }
    
    inline difference_type operator- (const iterator& b) const
    {
      return this->core_ - b.core_;
    }
    
    inline reference operator[]( int k ) const
    {
      return core_[k];
    }
    
    inline bool operator< (const iterator& b) const
    {
      return ( this->core_ - b.core_ ) < 0;
    }
    
    inline bool operator>  (const iterator& b) const
    {
      return ( this->core_ - b.core_ ) > 0;
    }
    
    inline bool operator>= (const iterator& b) const
    {
      return ( this->core_ - b.core_ ) >= 0;
    }
    
    inline bool operator<= (const iterator& b) const
    {
      return ( this->core_ - b.core_ ) <= 0;
    }
  };
  
  template< typename CT >
  index_iterator< CT >
  operator+( const typename index_iterator<CT>::difference_type & a,
            const index_iterator<CT>& b)
  {
    return b + a;
  }
}


#endif /* index_iterator_h */

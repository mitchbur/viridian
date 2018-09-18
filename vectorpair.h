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
    using value_type = std::tuple< _TA, _TB >;
    using reference = std::tuple< _TA&, _TB& >;
    using const_reference = std::tuple< const _TA&, const _TB& >;
    using pointer = void;
    using const_pointer = void;
    using iterator = vectorpair_iterator_<_TA,_TB>;

    std::vector< _TA > vector_a;
    std::vector< _TB > vector_b;
    
    std::size_t size( ) const
    {
      return std::min( vector_a.size(), vector_b.size() );
    }
    
    void push_back( value_type r )
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
    
    inline value_type operator[]( int k ) const
    {
      return std::make_tuple( vector_a[k], vector_b[k] );
    }
    
    inline reference operator[]( int k )
    {
      return std::tie( vector_a[k], vector_b[k] );
    }
    
    iterator begin( ) noexcept
    {
      return iterator{*this,0};
    }
    
    iterator end( ) noexcept
    {
      return iterator{*this,static_cast<typename iterator::difference_type>(this->size())};
    }
  };
  
  template< typename _TA, typename _TB >
  class vectorpair_iterator_
  {
  public:
    using container_type = vectorpair< _TA, _TB >;
    using iterator = typename container_type::iterator;

    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename container_type::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = void;
    using reference = typename container_type::reference;

  protected:
    container_type& container_;
    difference_type pos_;

  public:
    vectorpair_iterator_( ) = default;
    vectorpair_iterator_( container_type& c, difference_type i)
    : container_( c )
    , pos_(i){}
    
    // +--- input iterator
    // |
    // +--- forward iterator
    // |
    
    inline bool operator!= (const iterator& b) const
    {
      return ( this->pos_ != b.pos_ );
    }

    inline bool operator== (const iterator& b) const
    {
      return ( this->pos_ == b.pos_ );
    }
    
    inline reference operator*() const
    {
      return container_[this->pos_];
    }
    
    //! pre-increment operator
    inline iterator& operator++()
    {
      ++this->pos_;
      return *this;
    }
    //! post-increment operator
    inline iterator operator++(int)
    {
      iterator before = *this;
      ++this->pos_;
      return before;
    }

    // +--- bidirectional iterator
    // |

    //! pre-decrement operator
    inline iterator& operator--()
    {
      --this->pos_;
      return *this;
    }
    //! post-decrement operator
    inline iterator operator--(int)
    {
      iterator before = *this;
      --this->pos_;
      return before;
    }

    // +--- random access iterator
    // |
    
    inline iterator& operator+= (difference_type k) const
    {
      this->pos_ += k;
      return *this;
    }
    
    inline iterator operator+ (difference_type k) const
    {
      iterator b = *this;
      b += k;
      return b;
    }
    
    inline iterator& operator-= (difference_type k) const
    {
      this->pos_ -= k;
      return *this;
    }

    inline iterator operator- (difference_type k) const
    {
      iterator b = *this;
      b.pos_ -= k;
      return b;
    }
    
    inline difference_type operator- (const iterator& b) const
    {
      return this->pos_ - b.pos_;
    }
    
    inline reference operator[]( int k ) const
    {
      return container_[this->pos_+k];
    }
    
    inline bool operator< (const iterator& b) const
    {
      return ( this->pos_ < b.pos_ );
    }
    
    inline bool operator>  (const iterator& b) const
    {
      return ( this->pos_ > b.pos_ );
    }
    
    inline bool operator>= (const iterator& b) const
    {
      return ( this->pos_ >= b.pos_ );
    }

    inline bool operator<= (const iterator& b) const
    {
      return ( this->pos_ <= b.pos_ );
    }
  };
  
  template< typename _TA, typename _TB >
  inline typename vectorpair_iterator_<_TA,_TB>::iterator
  operator+ ( typename vectorpair_iterator_<_TA,_TB>::difference_type k,
             typename vectorpair_iterator_<_TA,_TB>::iterator& it )
  {
    return it + k;
  }
}

#endif /* vectorpair_h */

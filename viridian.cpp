#include "viridian.h"
#include <iostream>

void viridian::TagValueMapBase::clear( )
{
	p_map->clear();
}

viridian::TagValueMapBase::mapped_type& viridian::TagValueMapBase::operator[]( const key_type& key )
{
	return (*p_map)[ key ];
}

viridian::TagValueMapBase::mapped_type& viridian::TagValueMapBase::operator[]( key_type&& key )
{
	return (*p_map)[ key ];
}

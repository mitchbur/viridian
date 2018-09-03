#ifndef VIRIDIAN_H
#define VIRIDIAN_H

#include "viridian_config.h"
#include <map>
#include <string>
#include <memory>

namespace viridian {

	// tag/value map interface
	template< typename STR >
	class ITagValueMap
	{
	public:
		using MapType = std::map< STR, STR >;
		using key_type = typename MapType::key_type;
		using mapped_type = typename MapType::mapped_type;

		virtual ~ITagValueMap( ) = default;

		virtual void clear( ) = 0;
		virtual mapped_type& operator[]( const key_type& key ) = 0;
		virtual mapped_type& operator[]( key_type&& key ) = 0;

		// allow read-only direct access to map
		virtual const MapType& get_map( ) const = 0;
	};
	
	class TagValueMapBase : public ITagValueMap< std::string >
	{
	public:
		virtual ~TagValueMapBase() = default;

		virtual void clear( );
		virtual mapped_type& operator[]( const key_type& key );
		virtual mapped_type& operator[]( key_type&& key );

		virtual const MapType& get_map( ) const
		{
			return *p_map;
		}
		
	private:
		std::unique_ptr< MapType > p_map { new MapType };
	};
	
}

#endif

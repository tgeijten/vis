#pragma once

#include "mesh.h"
#include "node.h"
#include "types.h"
#include <vector>
#include "material.h"

namespace vis
{
	struct VIS_API trail_info
	{
		float radius_ = 0.1f;
		color color;
		float detail_ = 0.5f;
	};

	class VIS_API trail : public node
	{
	public:
		trail() : node( nullptr ), radius_(), color_(), detail_() {}
		trail( node& parent, const trail_info& ti );
		trail( node& parent, size_t num_points, float radius, color c, float detail = 0.5f );

		template< typename It >
		void set_points( It b, It e, float relative_width = 1.0f );

	private:
		void resize( size_t num_points );

		float radius_;
		color color_;
		float detail_;
		std::vector< mesh > points;
		std::vector< mesh > cylinders;
	};

	template< typename It >
	void trail::set_points( It b, It e, float relative_width )
	{
		if ( size_t( e - b ) != points.size() )
			resize( e - b );

		for ( size_t i = 0; i < points.size(); ++i )
			points[ i ].pos( vec3f( *( b + i ) ) );

		for ( size_t i = 0; i < cylinders.size(); ++i ) {
			auto start = vec3f( *( b + i ) );
			auto end = vec3f( *( b + i + 1 ) );
			cylinders[ i ].from_to_z( start, end, relative_width );
		}
	}
}

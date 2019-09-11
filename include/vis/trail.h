#pragma once

#include "osg/Group"
#include "mesh.h"
#include "node.h"

namespace vis
{
	class VIS_API trail : public node
	{
	public:
		trail() : node( nullptr ) {}
		trail( node& parent, size_t num_points, float radius, color c, float detail = 0.5f );

		trail( const trail& ) = delete;
		trail& operator=( const trail& ) = delete;
		trail( trail&& ) = default;
		trail& operator=( trail&& ) = default;

		template< typename Iter >
		void set_points( Iter b, Iter e, float relative_width = 1.0f );

	private:
		void resize( size_t num_points );

		color col;
		float detail;
		float radius;
		std::vector< mesh > points;
		std::vector< mesh > cylinders;
	};

	template< typename Iter >
	void vis::trail::set_points( Iter b, Iter e, float relative_width )
	{
		if ( e - b != points.size() ) resize( e - b );
		for ( size_t i = 0; i < points.size(); ++i )
			points[ i ].pos( vec3f( *( b + i ) ) );
		for ( size_t i = 0; i < cylinders.size(); ++i ) {
			auto& start = *( b + i );
			auto delta = *( b + i + 1 ) - start;
			cylinders[ i ].pos_ori( vec3f( start + 0.5f * delta ), quat_from_directions( vec3f::unit_z(), vec3f( normalized( delta ) ) ) );
			cylinders[ i ].scale( vec3f( relative_width, relative_width, xo::length( delta ) ) );
		}
	}
}

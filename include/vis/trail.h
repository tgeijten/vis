#pragma once

#include "mesh.h"
#include "node.h"
#include "types.h"
#include <vector>
#include "material.h"

namespace vis
{
	struct trail_info
	{
		float radius_ = 0.1f;
		color color_;
		float detail_ = 0.5f;
	};

	class trail : public node
	{
	public:
		trail() : node( nullptr ), radius_(), color_(), detail_() {}

		trail( node& parent, const trail_info& ti ) :
			node( &parent ),
			radius_( ti.radius_ ),
			color_( ti.color_ ),
			detail_( ti.detail_ )
		{}

		template< typename It >
		void set_points( It b, It e, float relative_width = 1.0f );

	private:
		float radius_;
		color color_;
		float detail_;
		std::vector< mesh > points;
		std::vector< mesh > cylinders;

		void resize( size_t num_points ) {
			size_t num_cylinders = num_points > 0 ? num_points - 1 : 0;

			// add points
			while ( points.size() < num_points )
				points.emplace_back( *this, xo::sphere{ radius_ * 1.02f }, color_, vec3f::zero(), detail_ );
			while ( cylinders.size() < num_cylinders )
				cylinders.emplace_back( *this, xo::cylinder{ radius_, 1.0f }, color_, vec3f( 0, 0, 0.5f ), detail_ );

			// remove points
			while ( points.size() > num_points )
				points.pop_back();

			while ( cylinders.size() > num_cylinders )
				cylinders.pop_back();
		}
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

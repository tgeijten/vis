#pragma once

#include "vis/types.h"
#include "vis/mesh.h"
#include "vis/node.h"

namespace vis
{
	struct arrow_info
	{
		float shaft_radius_;
		float head_radius_;
		color color_;
		float detail_ = 0.5f;
	};

	class arrow : public node
	{
	public:
		arrow() = default;
		arrow( node& parent, const arrow_info& info ) :
			node( &parent ),
			cylinder( *this, shape_info{ xo::cylinder{ info.shaft_radius_, 1 }, info.color_, vec3f( 0, 0, 0.5f ), info.detail_ } ),
			end_cone( *this, shape_info{ xo::cone{ info.head_radius_, info.head_radius_ * 2 }, info.color_, vec3f::zero(), info.detail_ } )
		{}

		void pos( const vec3f& begin_pos, const vec3f& end_pos ) {
			pos_ofs( begin_pos, end_pos - begin_pos );
		}

		void pos_ofs( const vec3f& pos, const vec3f& ofs ) {
			auto dir = ofs;
			auto l = normalize( dir );
			auto q = xo::quat_from_directions( vec3f::unit_z(), dir );
			cylinder.pos_ori( pos, q );
			cylinder.scale( vec3f( 1, 1, l ) );
			if ( end_cone.size() )
				end_cone.pos_ori( pos + ofs, q );
		}

		void set_color( const color& c )	{
			cylinder.set_color( c );
			end_cone.set_color( c );
		}

	private:
		mesh cylinder;
		mesh end_cone;
	};
}

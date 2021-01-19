#pragma once

#include "vis_api.h"
#include "mesh.h"
#include "node.h"

namespace vis
{
	class arrow : public node
	{
	public:
		arrow() = default;
		arrow( node& parent, float radius, float head_radius, const color& c, float detail = 0.5f ) :
			node( &parent ),
			cylinder( *this, xo::cylinder{ radius, 1 }, c, vec3f( 0, 0, 0.5f ), detail ),
			end_cone( *this, xo::cone{ head_radius, head_radius * 2 }, c, vec3f::zero(), detail )
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

#include "vis/arrow.h"

#include "xo/geometry/quat.h"
#include "xo/geometry/vec3.h"
#include "xo/system/log.h"

namespace vis
{
	arrow::arrow( node& parent, float radius, float head_radius, const color& c, float detail ) :
	node( &parent ),
	cylinder( *this, xo::cylinder{ radius, 1 }, c, vec3f( 0, 0, 0.5f ), detail ),
	end_cone( *this, xo::cone{ head_radius, head_radius * 2 }, c, vec3f::zero(), detail )
	{}

	void arrow::pos( const vec3f& begin_pos, const vec3f& end_pos )
	{
		vec3f dir = end_pos - begin_pos;
		auto q = xo::quat_from_directions( vec3f::unit_z(), dir );
		cylinder.pos_ori( begin_pos, q );
		cylinder.scale( vec3f( 1, 1, xo::length( dir ) ) );

		if ( end_cone.size() )
			end_cone.pos_ori( end_pos, q );
	}

	void arrow::set_color( const color& c )
	{
		cylinder.set_color( c );
		end_cone.set_color( c );
	}
}

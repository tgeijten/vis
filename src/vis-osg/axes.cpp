#include "vis/axes.h"

#include "vis/arrow.h"
#include "xo/geometry/quat.h"

namespace vis
{
	axes::axes( node& parent, vec3f length, float radius, float detail ) :
		node( &parent ),
		x_arrow( *this, xo::capsule{ radius, length.x }, color::red(), detail ),
		y_arrow( *this, xo::capsule{ radius, length.y }, color::green(), detail ),
		z_arrow( *this, xo::capsule{ radius, length.z }, color::blue(), detail )
	{
		x_arrow.pos_ori( vec3f( 0.5f * length.x, 0, 0 ), xo::quat_from_euler( degreef( 0 ), degreef( 90 ), degreef( 0 ) ) );
		y_arrow.pos_ori( vec3f( 0, 0.5f * length.y, 0 ), xo::quat_from_euler( degreef( 90 ), degreef( 0 ), degreef( 0 ) ) );
		z_arrow.pos( vec3f( 0, 0, 0.5f * length.z ) );
	}

	void axes::show( bool s )
	{
		x_arrow.show( s );
		y_arrow.show( s );
		z_arrow.show( s );
	}
}

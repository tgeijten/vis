#include "vis/axes.h"

#include "vis/arrow.h"
#include "xo/geometry/quat.h"

namespace vis
{
	axes::axes( node& parent, vec3f length, float radius, float detail ) :
		node( &parent ),
		x_arrow( *this, xo::capsule{ radius, length.x }, color::red(), vec3f( 0, 0, 0.5f * length.x ), detail ),
		y_arrow( *this, xo::capsule{ radius, length.y }, color::green(), vec3f( 0, 0, 0.5f * length.y ), detail ),
		z_arrow( *this, xo::capsule{ radius, length.z }, color::blue(), vec3f( 0, 0, 0.5f * length.z ), detail )
	{
		x_arrow.ori( xo::quat_from_euler( 0_degf, 90_degf, 0_degf ) );
		y_arrow.ori( xo::quat_from_euler( -90_degf, 0_degf, 0_degf ) );
	}

	void axes::show( bool s )
	{
		x_arrow.show( s );
		y_arrow.show( s );
		z_arrow.show( s );
	}
}

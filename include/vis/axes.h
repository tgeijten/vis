#pragma once

#include "vis_api.h"
#include "types.h"
#include "mesh.h"
#include "node.h"

namespace vis
{
	class axes : public node
	{
	public:
		axes() = default;
		axes( node& parent, vec3f length, float detail ) : axes( parent, length, 0.005f, detail ) {}
		axes( node& parent, vec3f length, float radius, float detail ) :
			node( &parent ),
			arrows_(
				mesh( *this, xo::capsule{ radius, length.x }, color::red(), vec3f( 0, 0, 0.5f * length.x ), detail ),
				mesh( *this, xo::capsule{ radius, length.y }, color::green(), vec3f( 0, 0, 0.5f * length.y ), detail ),
				mesh( *this, xo::capsule{ radius, length.z }, color::blue(), vec3f( 0, 0, 0.5f * length.z ), detail ) )
		{
			arrows_.x.ori( xo::quat_from_euler( 0_degf, 90_degf, 0_degf ) );
			arrows_.y.ori( xo::quat_from_euler( -90_degf, 0_degf, 0_degf ) );
		}

		bool show( bool s ) {
			arrows_.x.show( s );
			arrows_.y.show( s );
			arrows_.z.show( s );
			return s;
		}

		void axes::pos_ofs( const vec3f& pos, const xo::vec3_< vec3f >& dirs ) {
			for ( index_t i = 0; i < 3; ++i )
				arrows_[ i ].from_to_z( pos, pos + dirs[ i ] );
		}

	private:
		xo::vec3_<mesh> arrows_;
	};
}
 
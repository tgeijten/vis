#pragma once

#include "vis/types.h"
#include "vis/mesh.h"
#include "vis/node.h"

namespace vis
{
	struct axes_info {
		vec3f length_ = vec3f::diagonal( 0.1f );
		float radius_ = 0.005f;
		float detail_ = 0.5f;
	};

	class axes : public node
	{
	public:
		axes() = default;
		axes( node& parent, const axes_info& info ) :
			node( &parent ),
			arrows_(
				mesh( *this, shape_info{ xo::capsule{ info.radius_, info.length_.x }, color::red(), vec3f( 0, 0, 0.5f * info.length_.x ), info.detail_ } ),
				mesh( *this, shape_info{ xo::capsule{ info.radius_, info.length_.y }, color::green(), vec3f( 0, 0, 0.5f * info.length_.y ), info.detail_ } ),
				mesh( *this, shape_info{ xo::capsule{ info.radius_, info.length_.z }, color::blue(), vec3f( 0, 0, 0.5f * info.length_.z ), info.detail_ } ) )
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

		void pos_ofs( const vec3f& pos, const xo::vec3_< vec3f >& dirs ) {
			for ( index_t i = 0; i < 3; ++i )
				arrows_[ i ].from_to_z( pos, pos + dirs[ i ] );
		}

	private:
		xo::vec3_<mesh> arrows_;
	};
}
 
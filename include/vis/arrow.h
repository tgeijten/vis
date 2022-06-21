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
		arrow() : scale_threshold() {}
		arrow( node& parent, const arrow_info& info ) :
			node( &parent ),
			cylinder( *this, shape_info{ xo::cylinder{ info.shaft_radius_, 1 }, info.color_, vec3f( 0, 0, 0.5f ), info.detail_ } ),
			end_cone( *this, shape_info{ xo::cone{ info.head_radius_, info.head_radius_ * 2 }, info.color_, vec3f::zero(), info.detail_ } ),
			scale_threshold( info.head_radius_ * 6 )
		{
			cylinder.enable_normalize();
			end_cone.enable_normalize();
		}

		void pos( const vec3f& begin_pos, const vec3f& end_pos ) {
			pos_ofs( begin_pos, end_pos - begin_pos );
		}

		void pos_ofs( const vec3f& pos, const vec3f& ofs, float scale = 1.0f ) {
			vec3f dir = ofs;
			auto l = normalize( dir );
			if ( l < scale_threshold )
				scale *= l / scale_threshold;
			auto q = xo::quat_from_directions( vec3f::unit_z(), dir );
			cylinder.pos_ori( pos, q );
			cylinder.scale( vec3f( scale, scale, l ) );
			if ( end_cone.size() )
			{
				end_cone.pos_ori( pos + ofs, q );
				end_cone.scale( vec3f::diagonal( scale ) );
			}
		}

		void set_color( const color& c )	{
			cylinder.set_color( c );
			end_cone.set_color( c );
		}

	private:
		mesh cylinder;
		mesh end_cone;
		float scale_threshold;
	};
}

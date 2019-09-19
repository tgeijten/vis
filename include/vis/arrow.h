#pragma once

#include "vis_api.h"
#include "mesh.h"
#include "node.h"

namespace vis
{
	class VIS_API arrow : public node
	{
	public:
		arrow() {}
		arrow( node& parent, float radius, float head_radius, const color& c, float detail = 0.5f );
		arrow( const arrow& ) = delete;
		arrow& operator=( const arrow& ) = delete;
		arrow( arrow&& ) = default;
		arrow& operator=( arrow&& ) = default;

		void pos( const vec3f& begin_pos, const vec3f& end_pos );
		void pos_dir( const vec3f& pos, const vec3f& dir );
		void set_color( const color& c );

	private:
		mesh cylinder;
		mesh end_cone;
	};
}

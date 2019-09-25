#pragma once

#include "vis_api.h"
#include "types.h"
#include "node.h"

namespace vis
{
	class VIS_API scene : public node
	{
	public:
		scene( bool use_shadows, float ambient_intensity );

		light add_light( const vec3f& pos, const color& c );
	};
}

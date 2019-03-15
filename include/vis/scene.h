#pragma once

#include "mesh.h"
#include "arrow.h"
#include "trail.h"
#include "color.h"
#include "light.h"
#include "node.h"

namespace vis
{
	class VIS_API scene : public node
	{
	public:
		scene( bool use_shadows );

		scene( const scene& ) = delete;
		scene& operator=( const scene& ) = delete;
		scene( scene&& ) = default;
		scene& operator=( scene&& ) = default;

		light add_light( const vec3f& pos, const color& c );
	};
}

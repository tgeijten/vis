#pragma once

#include "mesh.h"
#include "node.h"
#include "arrow.h"

namespace vis
{
	class VIS_API axes : public node
	{
	public:
		axes( node& parent, vec3f length, float detail ) : axes( parent, length, 0.005f, detail ) {}
		axes( node& parent, vec3f length, float radius, float detail );
		axes( axes&& ) = default;
		axes& operator=( axes&& ) = default;

		void show( bool s );
		
	private:
		mesh x_arrow;
		mesh y_arrow;
		mesh z_arrow;
	};
}
 
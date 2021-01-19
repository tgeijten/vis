#pragma once

#include "vis/types.h"
#include "vis/node.h"

namespace vis
{
	class VIS_API scene : public node
	{
	public:
		scene( bool use_shadows, float ambient_intensity );
		~scene();
	};
}

#pragma once

#include "vis_api.h"
#include "types.h"
#include "mesh.h"
#include "node.h"

namespace vis
{
	class VIS_API axes : public node
	{
	public:
		axes() = default;
		axes( node& parent, vec3f length, float detail ) : axes( parent, length, 0.005f, detail ) {}
		axes( node& parent, vec3f length, float radius, float detail );

		bool show( bool s );
		void pos_ofs( const vec3f& pos, const xo::vec3_< vec3f >& dirs );
		
	private:
		xo::vec3_< mesh > arrows_;
	};
}
 
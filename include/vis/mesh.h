#pragma once

#include "vis_api.h"
#include "types.h"
#include "color.h"
#include "node.h"

#include "xo/filesystem/path.h"
#include "xo/shape/shape.h"

namespace vis
{
	class VIS_API mesh : public node
	{
	public:
		mesh( node& parent, const xo::path& filename );
		mesh( node& parent, const xo::shape& shape, const color& col, float detail = 0.75f );
		mesh( const mesh& ) = delete;
		mesh& operator=( const mesh& ) = delete;
		mesh( mesh&& ) = default;
		mesh& operator=( mesh&& ) = default;

		void set_color( const color& c );

	protected:
		handle<mesh> mesh_id_;
	};
}

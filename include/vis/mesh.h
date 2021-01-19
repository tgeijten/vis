#pragma once

#include "vis_api.h"
#include "types.h"
#include "node.h"

#include "xo/filesystem/path.h"
#include "xo/shape/shape.h"
#include "xo/system/log.h"

namespace vis
{
	class VIS_API mesh : public node
	{
	public:
		mesh() = default;
		mesh( node& parent, const xo::path& filename );
		mesh( node& parent, const xo::shape& shape, const color& col, const vec3f& center = vec3f::zero(), float detail = 0.75f );
		mesh( mesh&& o ) noexcept = default;
		mesh& operator=( mesh&& o ) noexcept = default;
		~mesh();

		void set_color( const color& c );

	protected:
		unique_handle<mesh> mesh_id_;
	};
}

#pragma once

#include "vis/types.h"
#include "vis/node.h"

#include "xo/filesystem/path.h"
#include "xo/shape/shape.h"

namespace vis
{
	struct shape_info {
		xo::shape shape_;
		color color_;
		vec3f center_ = vec3f::zero();
		float detail_ = 0.75f;
	};

	class VIS_API mesh : public node
	{
	public:
		mesh() = default;
		mesh( node& parent, const xo::path& filename );
		mesh( node& parent, const shape_info& info );
		mesh( mesh&& o ) noexcept = default;
		mesh& operator=( mesh&& o ) noexcept = default;
		~mesh();

		void set_color( const color& c );

	protected:
		unique_handle<mesh> mesh_id_;
	};
}

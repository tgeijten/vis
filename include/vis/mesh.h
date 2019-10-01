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
		mesh() {}
		mesh( node& parent, const xo::path& filename );
		mesh( node& parent, const xo::shape& shape, const color& col, const vec3f& center = vec3f::zero(), float detail = 0.75f );
		mesh( const mesh& ) = delete;
		mesh& operator=( const mesh& ) = delete;
		mesh( mesh&& o ) noexcept : node( std::move( o ) ), mesh_id_( o.mesh_id_ ) { o.mesh_id_.reset(); }
		mesh& operator=( mesh&& o ) noexcept { node::operator=( std::move( o ) ); mesh_id_.swap( o.mesh_id_ ); return *this; }
		~mesh();

		void set_color( const color& c );

	protected:
		handle<mesh> mesh_id_;
	};
}

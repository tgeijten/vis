#pragma once

#include "node.h"
#include "xo/filesystem/path.h"

namespace vis
{
	class VIS_API plane : public node
	{
	public:
		plane() {}
		plane( node& parent, const vec3f& width, const vec3f& height, const xo::path& image, float wrep = 1.0f, float hrep = 1.0f );
		plane( node& parent, int x_tiles, int z_tiles, float tile_size, color a, color b );

		plane( const plane& ) = delete;
		plane& operator=( const plane& ) = delete;
		plane( plane&& ) = default;
		plane& operator=( plane&& ) = default;
	};
}

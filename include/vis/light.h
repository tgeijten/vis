#pragma once

#include "vis_api.h"
#include "node.h"

namespace vis
{
	class VIS_API light
	{
	public:
		light() = default;
		light( scene& parent, const vec3f& pos, const color& col );
		light( const light& ) = delete;
		light& operator=( const light& ) = delete;
		light( light&& o ) noexcept : light_id_( o.light_id_ ) { o.light_id_.reset(); }
		light& operator=( light&& o ) noexcept { light_id_.swap( o.light_id_ ); return *this; }

		int get_number();

		void pos( const vec3f& p );
		void attenuation( float c, float l, float q );

	private:
		handle<light> light_id_;
		static int unique_light_number;
	};
}

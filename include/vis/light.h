#pragma once

#include "vis/types.h"

namespace vis
{
	class VIS_API light
	{
	public:
		light() = default;
		light( scene& parent, const vec3f& pos, const color& col );
		light( light&& o ) noexcept = default;
		light& operator=( light&& o ) noexcept = default;
		~light();

		int get_number();

		void pos( const vec3f& p );
		void attenuation( float c, float l, float q );

	private:
		unique_handle<light> light_id_;
		static int unique_light_number;
	};
}

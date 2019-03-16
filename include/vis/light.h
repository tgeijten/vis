#pragma once

#include "vis_api.h"
#include <osg/LightSource>
#include "node.h"

namespace vis
{
	class VIS_API light : public node
	{
	public:
		light() : light_id_() {}
		light( scene& parent, const vec3f& pos, const color& col );
		light( const light& ) = delete;
		light& operator=( const light& ) = delete;
		light( light&& ) = default;
		light& operator=( light&& ) = default;

		int get_number();

		void pos( const vec3f& p );
		void attenuation( float c, float l, float q );

	private:
		handle<light> light_id_;
		static int unique_light_number;
	};
}

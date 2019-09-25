#pragma once

#include "vis_api.h"
#include "types.h"

namespace vis
{
	struct VIS_API material_info
	{
		color diffuse_;
		color specular_;
		color ambient_;
		color emissive_;
		float shininess_;
	};

	class VIS_API material
	{
	public:
		material() {}
		material( color diffuse, color specular, float shininess, color ambient, color emissive );
		material( color diffuse, float specular, float shininess, float ambient, float emissive );
		material( const material& ) = delete;
		material& operator=( const material& ) = delete;
		material( material&& ) = default;
		material& operator=( material&& ) = default;
		~material();

		material clone() const;

		void set( color diffuse, color specular, float shininess, color ambient, color emissive );
		void set( color diffuse, float specular, float shininess, float ambient, float emissive );

		void diffuse( color col );
		void specular( color col );
		void ambient( color col );
		void emissive( color col );
		void shininess( float s );

		const handle<material>& material_id() { return material_id_; }

	private:
		handle<material> material_id_;
	};
}

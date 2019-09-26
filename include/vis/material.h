#pragma once

#include "vis_api.h"
#include "types.h"

namespace vis
{
	struct VIS_API material_info
	{
		material_info() : diffuse_(), specular_(), shininess_(), ambient_() {}
		material_info( const color& diffuse, const color& specular, float shininess, const color& ambient );
		material_info( const color& diffuse, float specular = 1.0f, float shininess = 30.0f, float ambient = 0.5f );

		color diffuse_;
		color specular_;
		float shininess_;
		color ambient_;
	};

	class VIS_API material
	{
	public:
		material() {}
		material( const material_info& mi );

		material( const material& ) = delete;
		material& operator=( const material& ) = delete;
		material( material&& ) = default;
		material& operator=( material&& ) = default;

		~material();

		material clone() const;

		void set( const material_info& mi );
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

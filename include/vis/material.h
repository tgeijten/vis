#pragma once

#include "vis/types.h"

namespace vis
{
	struct VIS_API material_info
	{
		material_info() : diffuse_(), specular_(), shininess_(), ambient_() {}
		material_info( const color& diffuse, const color& specular, float shininess, const color& ambient, float alpha = 1.0f );
		material_info( const color& diffuse, float specular = 1.0f, float shininess = 30.0f, float ambient = 0.5f, float alpha = 1.0f );

		color diffuse_;
		color specular_;
		float shininess_;
		color ambient_;
		float alpha_;
	};

	class VIS_API material
	{
	public:
		material() = default;
		material( const material_info& mi );
		material( material&& o ) noexcept = default;
		material& operator=( material&& o ) noexcept = default;
		~material();

		material clone() const;

		void set( const material_info& mi );
		void diffuse( color col );
		void specular( color col );
		void ambient( color col );
		void emissive( color col );
		void shininess( float s );
		void alpha( float a );

		const unique_handle<material>& material_id() const { return material_id_; }

	private:
		unique_handle<material> material_id_;
	};
}

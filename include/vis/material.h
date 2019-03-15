#pragma once

#include "color.h"
#include <osg/Material>

namespace vis
{
	class VIS_API material
	{
	public:
		material() : mat( new osg::Material ) {}
		material( osg::Material* m ) : mat( m ) {}
		material( const material& other ) : mat( other.mat ) {}
		material( color diffuse, color specular, float shininess, color ambient, color emissive );
		material( color diffuse, float specular, float shininess, float ambient, float emissive );
		virtual ~material() {}

		material clone() const;

		void set( color diffuse, color specular, float shininess, color ambient, color emissive );
		void set( color diffuse, float specular, float shininess, float ambient, float emissive );

		void diffuse( color col );
		void specular( color col );
		void ambient( color col );
		void emissive( color col );
		void shininess( float s );

		osg::Material* osg_mat() { return mat; }

	private:
		osg::ref_ptr< osg::Material > mat;
	};
}

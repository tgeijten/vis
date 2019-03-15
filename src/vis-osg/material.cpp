#include "vis/material.h"
#include "vis-osg/osg_tools.h"

namespace vis
{
	material::material( color diffuse, color specular, float shininess, color ambient, color emissive )
	{
		mat = new osg::Material;
		set( diffuse, specular, shininess, ambient, emissive );
	}

	material::material( color diffuse, float specular, float shininess, float ambient, float emissive )
	{
		mat = new osg::Material;
		set( diffuse, specular, shininess, ambient, emissive );
	}

	material material::clone() const
	{
		material m;
		*m.osg_mat() = *mat; // copy by value

		return m;
	}

	void material::set( color diffuse, color specular, float shininess, color ambient, color emissive )
	{
		mat->setDiffuse( osg::Material::FRONT_AND_BACK, to_osg( diffuse ) );
		mat->setSpecular( osg::Material::FRONT_AND_BACK, to_osg( specular ) );
		mat->setAmbient( osg::Material::FRONT_AND_BACK, to_osg( ambient ) );
		mat->setEmission( osg::Material::FRONT_AND_BACK, to_osg( emissive ) );
		mat->setShininess( osg::Material::FRONT_AND_BACK, shininess );
	}

	void material::set( color diffuse, float specular, float shininess, float ambient, float emissive )
	{
		mat->setDiffuse( osg::Material::FRONT_AND_BACK, to_osg( diffuse ) );
		mat->setSpecular( osg::Material::FRONT_AND_BACK, osg::Vec4( specular, specular, specular, 1 ) );
		mat->setAmbient( osg::Material::FRONT_AND_BACK, to_osg( diffuse ) * ambient );
		mat->setEmission( osg::Material::FRONT_AND_BACK, to_osg( diffuse ) * emissive );
		mat->setShininess( osg::Material::FRONT_AND_BACK, shininess );
	}

	void material::diffuse( color col )
	{
		mat->setDiffuse( osg::Material::FRONT_AND_BACK, to_osg( col ) );
	}

	void material::specular( color col )
	{
		mat->setSpecular( osg::Material::FRONT_AND_BACK, to_osg( col ) );
	}

	void material::ambient( color col )
	{
		mat->setAmbient( osg::Material::FRONT_AND_BACK, to_osg( col ) );
	}

	void material::emissive( color col )
	{
		mat->setEmission( osg::Material::FRONT_AND_BACK, to_osg( col ) );
	}

	void material::shininess( float s )
	{
		mat->setShininess( osg::Material::FRONT_AND_BACK, s );
	}
}

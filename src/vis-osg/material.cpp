#include "vis/material.h"
#include "vis-osg/osg_tools.h"
#include "vis-osg/osg_object_manager.h"

namespace vis
{
	material::material( color diffuse, color specular, float shininess, color ambient, color emissive ) :
		material_id_( osg_add<material>( new osg::Material ) )
	{
		set( diffuse, specular, shininess, ambient, emissive );
	}

	material::material( color diffuse, float specular, float shininess, float ambient, float emissive ) :
		material_id_( osg_add<material>( new osg::Material ) )
	{
		set( diffuse, specular, shininess, ambient, emissive );
	}

	material::~material()
	{
		if ( material_id_ )
			osg_remove( material_id_ );
	}

	material material::clone() const
	{
		auto cloned_osg = new osg::Material( osg_material( material_id_ ), osg::CopyOp::DEEP_COPY_ALL );
		material m;
		m.material_id_ = osg_add<material>( cloned_osg );
		return m;
	}

	void material::set( color diffuse, color specular, float shininess, color ambient, color emissive )
	{
		auto& m = osg_material( material_id_ );
		m.setDiffuse( osg::Material::FRONT_AND_BACK, to_osg( diffuse ) );
		m.setSpecular( osg::Material::FRONT_AND_BACK, to_osg( specular ) );
		m.setAmbient( osg::Material::FRONT_AND_BACK, to_osg( ambient ) );
		m.setEmission( osg::Material::FRONT_AND_BACK, to_osg( emissive ) );
		m.setShininess( osg::Material::FRONT_AND_BACK, shininess );
	}

	void material::set( color diffuse, float specular, float shininess, float ambient, float emissive )
	{
		auto& m = osg_material( material_id_ );
		m.setDiffuse( osg::Material::FRONT_AND_BACK, to_osg( diffuse ) );
		m.setSpecular( osg::Material::FRONT_AND_BACK, osg::Vec4( specular, specular, specular, 1 ) );
		m.setAmbient( osg::Material::FRONT_AND_BACK, to_osg( diffuse ) * ambient );
		m.setEmission( osg::Material::FRONT_AND_BACK, to_osg( diffuse ) * emissive );
		m.setShininess( osg::Material::FRONT_AND_BACK, shininess );
	}

	void material::diffuse( color col )
	{
		osg_material( material_id_ ).setDiffuse( osg::Material::FRONT_AND_BACK, to_osg( col ) );
	}

	void material::specular( color col )
	{
		osg_material( material_id_ ).setSpecular( osg::Material::FRONT_AND_BACK, to_osg( col ) );
	}

	void material::ambient( color col )
	{
		osg_material( material_id_ ).setAmbient( osg::Material::FRONT_AND_BACK, to_osg( col ) );
	}

	void material::emissive( color col )
	{
		osg_material( material_id_ ).setEmission( osg::Material::FRONT_AND_BACK, to_osg( col ) );
	}

	void material::shininess( float s )
	{
		osg_material( material_id_ ).setShininess( osg::Material::FRONT_AND_BACK, s );
	}
}

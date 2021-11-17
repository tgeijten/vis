#include "vis/material.h"
#include "vis-osg/osg_tools.h"
#include "vis-osg/osg_object_manager.h"

namespace vis
{
	material_info::material_info( const color& diffuse, const color& specular, float shininess, const color& ambient, float alpha ) :
		diffuse_( diffuse ),
		specular_( specular ),
		shininess_( shininess ),
		ambient_( ambient ),
		alpha_( alpha )
	{}

	material_info::material_info( const color& diffuse, float specular, float shininess, float ambient, float alpha ) :
		material_info( diffuse, specular* color::white(), shininess, ambient* diffuse, alpha )
	{}

	material::material( const material_info& mi ) :
		material_id_( osg_add<material>( new osg::Material ) )
	{
		set( mi );
	}

	material::~material()
	{
		if ( material_id_ )
			osg_remove( std::move( material_id_ ) );
	}

	material material::clone() const
	{
		material m;
		auto cloned_osg = new osg::Material( osg_material( material_id_ ), osg::CopyOp::DEEP_COPY_ALL );
		m.material_id_ = osg_add<material>( cloned_osg );
		return m;
	}

	void material::set( const material_info& mi )
	{
		auto& m = osg_material( material_id_ );
		m.setDiffuse( osg::Material::FRONT_AND_BACK, to_osg( mi.diffuse_ ) );
		m.setSpecular( osg::Material::FRONT_AND_BACK, to_osg( mi.specular_ ) );
		m.setAmbient( osg::Material::FRONT_AND_BACK, to_osg( mi.ambient_ ) );
		m.setEmission( osg::Material::FRONT_AND_BACK, osg::Vec4( 0, 0, 0, 0 ) ); // we don't use this
		m.setShininess( osg::Material::FRONT_AND_BACK, mi.shininess_ );
		m.setAlpha( osg::Material::FRONT_AND_BACK, mi.alpha_ );
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

	void material::alpha( float a )
	{
		osg_material( material_id_ ).setAlpha( osg::Material::FRONT_AND_BACK, a );
	}
}

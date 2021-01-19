#include "vis/light.h"
#include "vis/scene.h"

#include "vis-osg/osg_tools.h"
#include "vis-osg/osg_object_manager.h"
#include <osg/LightSource>

namespace vis
{
	int light::unique_light_number = 0;

	light::light( scene& parent, const vec3f& pos, const color& col )
	{
		auto l = new osg::Light;
		l->setLightNum( unique_light_number++ );

		l->setPosition( osg::Vec4f( pos.x, pos.y, pos.z, 1 ) );
		l->setDiffuse( to_osg( col ) );
		l->setSpecular( osg::Vec4( 1, 1, 1, 1 ) );
		l->setAmbient( osg::Vec4( 1, 1, 1, 1 ) );

		auto light_source = new osg::LightSource;
		light_source->setLight( l );
		light_source->setLocalStateSetModes( osg::StateAttribute::ON );
		light_source->setReferenceFrame( osg::LightSource::RELATIVE_RF );

		// directly add the light to the parent node
		// #todo: it should probably be added to its own node -- see if that's possible
		osg_group( parent.node_id() ).addChild( light_source );
		osg_group( parent.node_id() ).getOrCreateStateSet()->setMode( GL_LIGHT0 + get_number(), osg::StateAttribute::ON );
		light_id_ = osg_add<light>( light_source );
	}

	light::~light()
	{
		// #todo: cleanup light here?
	}

	int light::get_number()
	{
		return osg_get< osg::LightSource >( light_id_.value() ).getLight()->getLightNum();
	}

	void light::pos( const vec3f& pos )
	{
		osg_get< osg::LightSource >( light_id_.value() ).getLight()->setPosition( osg::Vec4f( pos.x, pos.y, pos.z, 1 ) );
	}

	void light::attenuation( float c, float l, float q )
	{
		auto& light_source = osg_get< osg::LightSource >( light_id_.value() );
		light_source.getLight()->setConstantAttenuation( c );
		light_source.getLight()->setLinearAttenuation( l );
		light_source.getLight()->setQuadraticAttenuation( q );
	}
}

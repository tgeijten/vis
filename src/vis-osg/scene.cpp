#include "vis/scene.h"
#include "vis/light.h"
#include "vis-osg/osg_tools.h"
#include "vis-osg/osg_object_manager.h"

#include "osgShadow/ShadowedScene"
#include "osgShadow/SoftShadowMap"
#include "osgDB/ObjectCache"
#include "osgDB/ReadFile"
#include "osg/LightModel"

namespace vis
{
	scene::scene( bool use_shadows, float ambient_intensity ) :
		node()
	{
		if ( use_shadows )
		{
			auto s_root = new osgShadow::ShadowedScene;

			/// setup shadows
			auto sm = new osgShadow::SoftShadowMap;
			sm->setTextureSize( osg::Vec2s( 1024, 1024 ) );
			s_root->setShadowTechnique( sm );
			//sm->setAmbientBias( osg::Vec2( 0.5f, 0.5f ) );

			auto ss = new osgShadow::ShadowSettings;
			ss->setCastsShadowTraversalMask( OsgCastShadowMask );
			ss->setReceivesShadowTraversalMask( OsgReceiveShadowMask ); // this one doesn't do anything in osg
			s_root->setShadowSettings( ss );

			node_id_ = osg_add<node>( s_root );
		}
		else
		{
			node_id_ = osg_add<node>( new osg::Group );
		}

		auto& node = osg_node( node_id_ );

		// enable lighting
		node.getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON );

		// set default lighting
		osg::ref_ptr< osg::Material > mat = new osg::Material;
		mat->setSpecular( osg::Material::FRONT, osg::Vec4( 1, 1, 1, 1 ) );
		mat->setEmission( osg::Material::FRONT, osg::Vec4( 0, 0, 0, 1 ) );
		mat->setShininess( osg::Material::FRONT, 25.0 );
		mat->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
		node.getOrCreateStateSet()->setAttribute( mat );

		// set ambient intensity (for some reason, this requires yet another light class)
		osg::ref_ptr< osg::LightModel > lm = new osg::LightModel;
		//lm->setAmbientIntensity( osg::Vec4( 0.333, 0.333, 0.333, 1 ) );
		lm->setAmbientIntensity( osg::Vec4( ambient_intensity, ambient_intensity, ambient_intensity, 1 ) );
		node.getOrCreateStateSet()->setAttribute( lm );
	}

	scene::~scene()
	{
		// #todo: cleanup scene (and lights?) here?
	}
}

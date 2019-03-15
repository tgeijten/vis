#include "vis/node.h"
#include "vis/material.h"

#include "xo/shape/shape.h"

#include "vis-osg/osg_tools.h"
#include "osg_object_manager.h"

namespace vis
{
	using xo::shape;
	using xo::shape_type;

	node::node( node* parent )
	{
		if ( parent )
		{
			node_id_ = osg_add( new osg::PositionAttitudeTransform );
			parent->attach( *this );
		}
		else node_id_ = no_index;
	}

	node::~node()
	{
		release();
	}

	void node::attach( node& o )
	{
		osg_get< osg::Group >( node_id_ ).addChild( &osg_get< osg::Node >( o.node_id_ ) );
	}

	void node::detach( node& o )
	{
		osg_get< osg::Group >( node_id_ ).removeChild( &osg_get< osg::Node >( o.node_id_ ) );
	}

	void node::detach_all()
	{
		osg_get< osg::Group >( node_id_ ).removeChildren( 0, osg_get< osg::Group >( node_id_ ).getNumChildren() );
	}

	void node::release()
	{
		if ( node_id_ != no_index )
		{
			auto& group = osg_get< osg::Group >( node_id_ );
			if ( group.referenceCount() == group.getNumParents() + 1 )
			{
				// this is the last ref, so remove from all parents
				while ( group.getNumParents() > 0 )
					group.getParent( 0 )->removeChild( &group );
			}
		}
	}

	size_t node::size() const
	{
		return osg_get< osg::Group >( node_id_ ).getNumChildren();
	}

	void node::show( bool show )
	{
		// this resets any node mask related setting
		// TODO: find a better way to show/hide nodes
		osg_get< osg::Group >( node_id_ ).setNodeMask( show ? ~0 : 0 );
	}

	void node::set_material( material& m )
	{
		osg_get< osg::Node >( node_id_ ).getOrCreateStateSet()->setAttribute( m.osg_mat() );
	}

	bool node::has_parent() const
	{
		return osg_get< osg::Node >( node_id_ ).getNumParents() > 0;
	}

	void node::transform( const transformf& t )
	{
		auto& transnode = osg_get< osg::PositionAttitudeTransform >( node_id_ );
		transnode.setPosition( to_osg( t.p ) );
		transnode.setAttitude( to_osg( t.q ) );
	}

	void node::pos( const vec3f& p )
	{
		osg_get< osg::PositionAttitudeTransform >( node_id_ ).setPosition( to_osg( p ) );
	}

	void node::ori( const quatf& q )
	{
		osg_get< osg::PositionAttitudeTransform >( node_id_ ).setAttitude( to_osg( q ) );
	}

	void node::scale( const vec3f& s )
	{
		osg_get< osg::PositionAttitudeTransform >( node_id_ ).setScale( to_osg( s ) );
	}
}

#include "vis/node.h"
#include "vis/material.h"

#include "xo/shape/shape.h"

#include "vis-osg/osg_tools.h"
#include "vis-osg/osg_object_manager.h"

namespace vis
{
	using xo::shape;

	node::node( node* parent )
	{
		if ( parent )
		{
			node_id_ = osg_add<node>( new osg::PositionAttitudeTransform );
			parent->attach( *this );
		}
	}

	node::~node()
	{
		release();
	}

	void node::attach( node& o )
	{
		osg_group( node_id_ ).addChild( &osg_node( o.node_id_ ) );
	}

	void node::detach( node& o )
	{
		osg_group( node_id_ ).removeChild( &osg_node( o.node_id_ ) );
	}

	void node::detach_all()
	{
		osg_group( node_id_ ).removeChildren( 0, osg_group( node_id_ ).getNumChildren() );
	}

	void node::release()
	{
		if ( node_id_ )
		{
			auto& group = osg_group( node_id_ );
			if ( group.referenceCount() == group.getNumParents() + 1 )
			{
				// this is the last ref, so remove from all parents
				while ( group.getNumParents() > 0 )
					group.getParent( 0 )->removeChild( &group );
				osg_remove( node_id_ );
			}
		}
	}

	size_t node::size() const
	{
		return osg_group( node_id_ ).getNumChildren();
	}

	bool node::show( bool show )
	{
		// this resets any node mask related setting
		// #todo: find a better way to show/hide nodes
		auto& g = osg_group( node_id_ );
		g.setNodeMask( show ? ~0 : 0 );
		return show;
	}

	void node::set_material( material& m )
	{
		osg_node( node_id_ ).getOrCreateStateSet()->setAttribute( &osg_material( m.material_id() ) );
	}

	bool node::has_parent() const
	{
		return osg_node( node_id_ ).getNumParents() > 0;
	}

	void node::transform( const transformf& t )
	{
		auto& transnode = osg_trans( node_id_ );
		transnode.setPosition( to_osg( t.p ) );
		transnode.setAttitude( to_osg( t.q ) );
	}

	void node::pos( const vec3f& p )
	{
		osg_trans( node_id_ ).setPosition( to_osg( p ) );
	}

	void node::ori( const quatf& q )
	{
		osg_trans( node_id_ ).setAttitude( to_osg( q ) );
	}

	void node::from_to_z( const vec3f& from, const vec3f& to, float width )
	{
		vec3f delta = to - from;
		auto length = normalize( delta );
		pos_ori( from, xo::quat_from_directions( vec3f::unit_z(), delta ) );
		scale( vec3f( width, width, length ) );
	}

	void node::scale( const vec3f& s )
	{
		osg_trans( node_id_ ).setScale( to_osg( s ) );
	}
}

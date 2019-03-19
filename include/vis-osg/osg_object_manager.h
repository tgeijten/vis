#pragma once

#include "vis/vis_api.h"
#include "vis/types.h"

#include <osg/ref_ptr>
#include <osg/Object>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>

namespace vis
{
	struct VIS_API osg_object_manager
	{
	public:
		osg_object_manager() {}

		index_t add( osg::Object* o ) { data_.emplace_back( o ); return data_.size() - 1; }
		template< typename T > T& get( index_t i ) { return dynamic_cast< T& >( *data_[ i ] ); }
		void remove( index_t i ) { data_[ i ] = nullptr; }

		std::vector< osg::ref_ptr< osg::Object > > data_;

		static osg_object_manager global_instance_;
	};

	template< typename T > handle< T > osg_add( osg::Object* o ) { return osg_object_manager::global_instance_.add( o ); }
	template< typename T > T& osg_get( uint32_t i ) { return osg_object_manager::global_instance_.get< T >( i ); }
	inline osg::Group& osg_group( handle< node > i ) { return osg_get< osg::Group >( i.value ); }
	inline osg::Node& osg_node( handle< node > i ) { return osg_get< osg::Node >( i.value ); }
	inline osg::PositionAttitudeTransform& osg_trans( handle< node >  i ) { return osg_get< osg::PositionAttitudeTransform >( i.value ); }
}
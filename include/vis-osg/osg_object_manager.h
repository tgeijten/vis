#pragma once

#include "vis/vis_api.h"
#include "vis/types.h"

#include <osg/ref_ptr>
#include <osg/Object>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Material>
#include "xo/system/log.h"
#include "xo/system/system_tools.h"
#include "xo/xo_types.h"

namespace vis
{
	// #todo: use xo::proxy
	struct VIS_API osg_object_manager
	{
	public:
		osg_object_manager();

		index_t add( osg::Object* o );
		void remove( index_t i );
		osg::Object* get( index_t i ) { xo_assert( i < data_.size() ); return data_[ i ]; }
		size_t size() const { return data_.size(); }
		size_t min_size() const;
		void shrink_to_fit();

		static osg_object_manager global_instance_;

	private:
		index_t idx_;
		std::vector< osg::ref_ptr< osg::Object > > data_;
	};

	template< typename T > unique_handle<T> osg_add( osg::Object* o ) {
		auto idx = osg_object_manager::global_instance_.add( o );
		xo::log::debug( "Added ", xo::get_clean_type_name<T>(), idx, " size=", osg_object_manager::global_instance_.min_size() );
		return unique_handle<T>( idx );
	}
	template< typename T > void osg_remove( unique_handle<T> i ) {
		xo::log::debug( "Removing ", xo::get_clean_type_name<T>(), i.value(), " size=", osg_object_manager::global_instance_.min_size() );
		return osg_object_manager::global_instance_.remove( i.value() );
	}

	template< typename T > T& osg_get( xo::uint32 i ) {
		auto* obj = osg_object_manager::global_instance_.get( i );
		xo_assert( obj );
		return dynamic_cast<T&>( *obj );
	}

	inline osg::Group& osg_group( const unique_handle< node >& i ) { return osg_get< osg::Group >( i.value() ); }
	inline osg::Node& osg_node( const unique_handle< node >& i ) { return osg_get< osg::Node >( i.value() ); }
	inline osg::PositionAttitudeTransform& osg_trans( const unique_handle< node >& i ) { return osg_get< osg::PositionAttitudeTransform >( i.value() ); }
	inline osg::Material& osg_material( const unique_handle< material >& i ) { return osg_get< osg::Material >( i.value() ); }
}

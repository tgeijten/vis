#include "vis-osg/osg_object_manager.h"
#include "xo/system/log.h"

namespace vis
{
	osg_object_manager::osg_object_manager() : idx_( 0 )
	{}

	index_t osg_object_manager::add( osg::Object* o )
	{
		if ( idx_ == data_.size() )
		{
			// must grow vector
			data_.emplace_back( o );
			return idx_++;
		}
		else
		{
			xo_assert( !data_[idx_] );
			data_[idx_] = o;

			index_t ret_idx = idx_;

			// move idx to next free entry or end
			++idx_;
			while ( idx_ < data_.size() && data_[idx_] )
				++idx_;

			return ret_idx;
		}
	}

	void osg_object_manager::remove( index_t i )
	{
		xo_assert( data_[i] );
		data_[i] = nullptr;
		if ( i < idx_ )
			idx_ = i; // set next idx

		// #todo: shrink_to_fit?
	}

	size_t osg_object_manager::min_size() const
	{
		auto it = data_.rbegin();
		while ( it != data_.rend() && !*it )
			++it;
		return data_.rend() - it;
	}

	void osg_object_manager::shrink_to_fit()
	{
		data_.resize( min_size() );
	}

	osg_object_manager osg_object_manager::global_instance_;
}

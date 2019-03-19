#pragma once

#include "vis_api.h"
#include "types.h"

namespace vis
{
	class VIS_API node
	{
	public:
		node( node* parent = nullptr );
		node( const node& ) = delete;
		node& operator=( const node& ) = delete;
		node( node&& ) = default;
		node& operator=( node&& ) = default;
		~node();

		void attach( node& o );
		void detach( node& o );
		void detach_all();
		void release();

		size_t size() const;
		bool has_parent() const;

		void show( bool show );
		void set_material( material& m );

		void transform( const transformf& t );
		void pos( const vec3f& p );
		void ori( const quatf& q );
		void pos_ori( const vec3f& p, const quatf& q ) { pos( p ); ori( q ); }
		void scale( const vec3f& s );

		const handle<node>& node_id() const { return node_id_; }

	protected:
		handle<node> node_id_;
	};
}

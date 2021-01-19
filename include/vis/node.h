#pragma once

#include "vis/types.h"

namespace vis
{
	class VIS_API node
	{
	public:
		node( node* parent = nullptr );
		node( node&& o ) noexcept = default;
		node& operator=( node&& o ) noexcept = default;
		~node();

		void attach( node& o );
		void detach( node& o );
		void detach_all();
		void release();

		size_t size() const;
		bool has_parent() const;

		bool show( bool show );
		void set_material( material& m );

		void transform( const transformf& t );
		void pos( const vec3f& p );
		void ori( const quatf& q );
		void pos_ori( const vec3f& p, const quatf& q );
		void from_to_z( const vec3f& from, const vec3f& to, float width = 1.0f );
		void scale( const vec3f& s );

		const unique_handle<node>& node_id() const { return node_id_; }

	protected:
		unique_handle<node> node_id_;
	};
}

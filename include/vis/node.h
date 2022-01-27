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
		void set_material( const material& m );

		void transform( const transformf& t );
		void pos( const vec3f& p );
		void ori( const quatf& q );
		void pos_ori( const vec3f& p, const quatf& q );
		void from_to_z( const vec3f& from, const vec3f& to, float width = 1.0f );
		void scale( const vec3f& s );
		void enable_normalize();
		void scale_enable_normalize( const vec3f& s );

		void set_cast_shadows( bool b );
		void set_receive_shadows( bool b );

		const unique_handle<node>& node_id() const { return node_id_; }
		void set_name( const char* name );
		const char* get_name() const;

	protected:
		unique_handle<node> node_id_;
	};
}

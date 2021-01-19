#pragma once

#include "xo/xo_types.h"

namespace vis
{
	template< typename T, typename I = xo::uint32 >
	struct unique_handle {
		using object_type = T;
		using id_type = I;

		// constructor
		constexpr unique_handle() : value_( invalid_id() ) {}

		// delete copy constructor / assignment
		unique_handle( const unique_handle& o ) = delete;
		unique_handle& operator=( const unique_handle& o ) = delete;

		// move constructor / assignment
		unique_handle( unique_handle&& o ) noexcept : value_( o.value_ ) { o.reset(); }
		unique_handle& operator=( unique_handle&& o ) noexcept { std::swap( value_, o.value_ ); return *this; }

		// explicit conversion constructor
		explicit constexpr unique_handle( id_type v ) : value_( v ) {}

		// inspect value
		explicit operator bool() const { return value_ != invalid_id(); }
		const id_type& value() const { return value_; }
		id_type& value() { return value_; }

		void reset() { value_ = invalid_id(); }

	private:
		static constexpr id_type invalid_id() { return ~id_type( 0 ); }
		id_type value_;
	};
}

#pragma once

#include "vis/types.h"
#include "camera_state.h"
#include "xo/container/flat_map.h"
#include "xo/time/time.h"
#include "xo/numerical/functions.h"

namespace vis
{
	enum class interpolation_type {
		linear,
		minimum_jerk
	};

	struct camera_animation {
		using time_t = double;

		time_t start_time() const { return states_.empty() ? time_t{} : states_.front().first; }
		time_t stop_time() const { return states_.empty() ? time_t{} : states_.back().first; }

		bool active( time_t t ) const { return !states_.empty() && t >= start_time() && t <= stop_time(); }
		bool empty() const { return states_.empty(); }
		void insert( time_t t, const camera_state& cs ) { states_[t] = cs; }
		void clear() { states_.clear(); }

		camera_state get( time_t t ) {
			xo_assert( !empty() );
			auto it = states_.upper_bound( t );
			if ( it == states_.end() )
				return states_.back().second;
			else if ( it == states_.begin() )
				return states_.front().second;
			else {
				auto it0 = it - 1;
				auto w = static_cast<real>( ( t - it0->first ) / ( it->first - it0->first ) );
				return vis::lerp( it0->second, it->second, interpolation_factor( w ) );
			}
		}

	private:
		real interpolation_factor( real t ) {
			switch ( interpolation_type_ ) {
			case interpolation_type::linear: return t;
			case interpolation_type::minimum_jerk: return xo::minimum_jerk( t );
			default: return real( 0 );
			}
		}

		xo::flat_map<time_t, camera_state> states_;
		interpolation_type interpolation_type_ = interpolation_type::minimum_jerk;
	};
}

#pragma once

#include "vis/vis_api.h"
#include "xo/geometry/vec3_type.h"
#include "xo/geometry/quat_type.h"
#include "xo/geometry/transform.h"
#include "xo/geometry/angle_type.h"
#include "xo/utility/color.h"
#include "vis/unique_handle.h"

namespace vis
{
	class axes;
	class node;
	class scene;
	class mesh;
	class arrow;
	class trail;
	class arrow;
	class light;
	class material;

	using real = float;
	using xo::color;
	using xo::vec3f;
	using xo::quatf;
	using xo::transformf;
	using xo::degreef;
	using xo::radianf;
	using xo::index_t;
	using namespace xo::angle_literals;
}

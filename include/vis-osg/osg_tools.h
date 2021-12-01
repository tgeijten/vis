#pragma once

#include "vis/vis_api.h"
#include "vis/types.h"
#include "xo/filesystem/path.h"

#include <osg/Vec3f>
#include <osg/Vec4f>
#include <osg/Quat>
#include <osg/Geode>

namespace vis
{
	const int OsgReceiveShadowMask = 0x1;
	const int OsgCastShadowMask = 0x2;

	inline osg::Vec3f to_osg( const vec3f& v ) { return osg::Vec3f( v.x, v.y, v.z ); }
	inline osg::Vec4f to_osg( const vec4f& v ) { return osg::Vec4f( v.x, v.y, v.z, v.w ); }
	inline osg::Quat to_osg( const quatf& v ) { return osg::Quat( v.x, v.y, v.z, v.w ); }
	inline osg::Vec4f to_osg( const xo::color& v ) { return osg::Vec4f( v.r, v.g, v.b, v.a ); }

	inline quatf from_osg( const osg::Quat& v ) { return quatf( v.w(), v.x(), v.y(), v.z() ); }
	inline vec3f from_osg( const osg::Vec3f& v ) { return vec3f( v.x(), v.y(), v.z() ); }

	VIS_API osg::Geode* read_vtp( const xo::path& filename );
	VIS_API void set_shadow_mask( osg::Node* n, bool receive, bool cast );
}

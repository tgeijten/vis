#include "vis/mesh.h"
#include "vis/scene.h"

#include "xo/string/string_tools.h"

#include "vis-osg/osg_tools.h"
#include "osgDB/ReadFile"
#include "osg/ShapeDrawable"
#include "osg/Material"
#include "vis-osg/osg_object_manager.h"

namespace vis
{
	using xo::shape;

	mesh::mesh( node& parent, const xo::path& filename ) :
	node( &parent )
	{
		osg::Node* file_node;
		if ( filename.extension_no_dot() == "vtp" )
			file_node = read_vtp( filename );
		else // #todo #issue87: add support for .obj and other formats
			file_node = osgDB::readNodeFile( filename.str() );

		if ( file_node )
		{
			mesh_id_ = osg_add<mesh>( file_node );
			osg_group( node_id_ ).addChild( file_node );
		}
	}

	struct create_shape_visitor {
		create_shape_visitor( osg::TessellationHints* hints, const osg::Vec3& center ) : hints_( hints ), center_( center ) {}

		osg::ShapeDrawable* operator()( const xo::sphere& s ) {
			return new osg::ShapeDrawable( new osg::Sphere( center_, s.radius_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::box& s ) {
			auto d = dim( s );
			return new osg::ShapeDrawable( new osg::Box( center_, d.x, d.y, d.z ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::cylinder& s ) {
			return new osg::ShapeDrawable( new osg::Cylinder( center_, s.radius_, s.height_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::capsule& s ) {
			return new osg::ShapeDrawable( new osg::Capsule( center_, s.radius_, s.height_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::cone& s ) {
			return new osg::ShapeDrawable( new osg::Cone( center_, s.radius_, s.height_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::plane& s ) {
			xo_error( "Cannot create mesh from shape" );
		}

		osg::TessellationHints* hints_;
		osg::Vec3 center_;
	};

	mesh::mesh( node& parent, const shape_info& info ) :
	node( &parent )
	{
		auto hints = new osg::TessellationHints;
		hints->setDetailRatio( info.detail_ );

		osg::ref_ptr< osg::ShapeDrawable > sd = std::visit( create_shape_visitor( hints, to_osg( info.center_ ) ), info.shape_ );
		sd->setColor( to_osg( info.color_ ) );
		auto g = new osg::Geode;
		g->addDrawable( sd );
		mesh_id_ = osg_add<mesh>( g );
		osg_group( node_id_ ).addChild( g );
	}

	mesh::~mesh()
	{
		if ( mesh_id_ )
			osg_remove( std::move( mesh_id_ ) );
	}

	void mesh::set_color( const color& c )
	{
		dynamic_cast<osg::ShapeDrawable&>( *osg_get< osg::Geode >( mesh_id_.value() ).getDrawable( 0 ) ).setColor( to_osg( c ) );
	}
}

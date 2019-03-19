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
	using xo::shape_type;

	mesh::mesh( node& parent, const xo::path& filename ) :
	node( &parent )
	{
		osg::Node* file_node;
		if ( filename.extension() == "vtp" )
			file_node = read_vtp( filename );
		else
			file_node = osgDB::readNodeFile( filename.string() );

		mesh_id_ = osg_add<mesh>( file_node );
		osg_group( node_id_ ).addChild( file_node );
	}

	struct create_shape_visitor {
		create_shape_visitor( osg::TessellationHints* hints ) : hints_( hints ) {}

		osg::ShapeDrawable* operator()( const xo::sphere& s ) {
			return new osg::ShapeDrawable( new osg::Sphere( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::box& s ) {
			auto d = dim( s );
			return new osg::ShapeDrawable( new osg::Box( osg::Vec3( 0.0f, 0.0f, 0.0f ), d.x, d.y, d.z ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::cylinder& s ) {
			return new osg::ShapeDrawable( new osg::Cylinder( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius_, s.height_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::capsule& s ) {
			return new osg::ShapeDrawable( new osg::Capsule( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius_, s.height_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::cone& s ) {
			return new osg::ShapeDrawable( new osg::Cone( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius_, s.height_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::plane& s ) {
			xo_error( "Cannot create mesh from shape" );
		}

		osg::TessellationHints* hints_;
	};

	mesh::mesh( node& parent, const shape& s, const color& col, float detail ) :
	node( &parent )
	{
		auto hints = new osg::TessellationHints;
		hints->setDetailRatio( detail );

		osg::ref_ptr< osg::ShapeDrawable > sd = std::visit( create_shape_visitor( hints ), s );
		sd->setColor( to_osg( col ) );
		auto g = new osg::Geode;
		g->addDrawable( sd );
		mesh_id_ = osg_add<mesh>( g );
		osg_group( node_id_ ).addChild( g );
	}

	mesh::~mesh()
	{
		if ( mesh_id_ )
			osg_remove( mesh_id_ );
	}

	void mesh::set_color( const color& c )
	{
		dynamic_cast<osg::ShapeDrawable&>( *osg_get< osg::Geode >( mesh_id_.value ).getDrawable( 0 ) ).setColor( to_osg( c ) );
	}
}

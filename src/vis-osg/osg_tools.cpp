#include "vis-osg/osg_tools.h"

#include <osg/Geometry>
#include <osg/Material>
#include "xo/container/prop_node.h"
#include "xo/system/log.h"
#include "xo/time/timer_v1.h"
#include "xo/container/prop_node_tools.h"
#include "xo/serialization/serialize.h"
#include "xo/serialization/char_stream.h"

namespace vis
{
	/// convert space-delimited string to vector of elements
	template< typename T > std::vector< T > str_to_vec( const std::string& s, size_t max_values, const char* delim = xo::whitespace_characters ) {
		xo::char_stream str( s.c_str(), delim );
		std::vector< T > vec; if ( max_values != xo::no_index ) vec.reserve( max_values );
		while ( str.good() && vec.size() < max_values ) { T elem; str >> elem; if ( !str.fail() ) vec.push_back( elem ); }
		return vec;
	}

	VIS_API osg::Geode* read_vtp( const xo::path& filename )
	{
		xo::prop_node root_pn = load_file( filename, "xml" );
		xo::prop_node& poly_pn = root_pn[ "VTKFile" ][ "PolyData" ][ "Piece" ];
		auto point_count = poly_pn.get< int >( "NumberOfPoints");
		auto poly_count = poly_pn.get< int >( "NumberOfPolys" );

		// create normal and vertex array
		osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array( point_count );
		osg::Vec3Array* vertices = new osg::Vec3Array( point_count );

		auto normal_vec = str_to_vec< float >( poly_pn[ "PointData" ][ "DataArray" ].get_value(), point_count * 3 );
		auto point_vec = str_to_vec< float >( poly_pn[ "Points" ][ "DataArray" ].get_value(), point_count * 3 );

		xo_assert( normal_vec.size() == point_count * 3 && point_vec.size() == point_count * 3 );

		size_t vec_idx = 0;
		for ( int idx = 0; idx < point_count; ++idx )
		{
			normals->at( idx ).set( normal_vec[ vec_idx ], normal_vec[ vec_idx + 1 ], normal_vec[ vec_idx  + 2] );
			vertices->at( idx ).set( point_vec[ vec_idx ], point_vec[ vec_idx + 1 ], point_vec[ vec_idx  + 2] );
			vec_idx += 3;
		}

		osg::ref_ptr< osg::DrawElementsUShort > trianglePrimitives = new osg::DrawElementsUShort( GL_TRIANGLES );
		osg::ref_ptr< osg::DrawElementsUShort > quadPrimitives = new osg::DrawElementsUShort( GL_QUADS );

		{
			auto con_vec = str_to_vec< int >( poly_pn[ "Polys" ][ 0 ].get_value(), xo::no_index );
			auto ofs_vec = str_to_vec< int >( poly_pn[ "Polys" ][ 1 ].get_value(), xo::no_index );
			
			for ( size_t idx = 0; idx < ofs_vec.size(); ++idx )
			{
				auto end_ofs = ofs_vec[ idx ];
				auto begin_ofs = idx == 0 ? (unsigned short)( 0 ) : ofs_vec[ idx - 1 ];
				auto num_ver = end_ofs - begin_ofs;
				if ( num_ver == 3 )
				{
					trianglePrimitives->push_back( (unsigned short) con_vec[begin_ofs] );
					trianglePrimitives->push_back( (unsigned short) con_vec[begin_ofs + 1] );
					trianglePrimitives->push_back( (unsigned short) con_vec[begin_ofs + 2] );
				}
				else if ( num_ver == 4 )
				{
					quadPrimitives->push_back( (unsigned short) con_vec[begin_ofs] );
					quadPrimitives->push_back( (unsigned short) con_vec[begin_ofs + 1] );
					quadPrimitives->push_back( (unsigned short) con_vec[begin_ofs + 2] );
					quadPrimitives->push_back( (unsigned short) con_vec[begin_ofs + 3] );
				}
				else
				{
					// silently ignore...
					//xo::log::warning( "Unknown primitive type, number of vertices = ", num_ver );
				}
			}
		}

		// add primitives
		osg::Geometry* polyGeom = new osg::Geometry;
		if ( trianglePrimitives->size() > 0 )
			polyGeom->addPrimitiveSet( trianglePrimitives );
		if ( quadPrimitives->size() > 0 )
			polyGeom->addPrimitiveSet( quadPrimitives );

		// create color array (shared)
		//osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
		//shared_colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
		//polyGeom->setColorArray( shared_colors.get(), osg::Array::BIND_OVERALL );

		// pass the created vertex array to the points geometry object
		polyGeom->setVertexArray( vertices );
		polyGeom->setNormalArray( normals, osg::Array::BIND_PER_VERTEX );
		polyGeom->setCullingActive( true );

		// add the points geometry to the geode.
		osg::Geode* geode = new osg::Geode;
		geode->addDrawable(polyGeom);
		geode->getOrCreateStateSet()->setMode( GL_CULL_FACE, osg::StateAttribute::ON );

		return geode;
	}

	void set_shadow_mask( osg::Node* n, bool receive, bool cast )
	{
		n->setNodeMask( receive ? n->getNodeMask() | OsgReceiveShadowMask : n->getNodeMask() & ~OsgReceiveShadowMask );
		n->setNodeMask( cast ? n->getNodeMask() | OsgCastShadowMask : n->getNodeMask() & ~OsgCastShadowMask );
	}
}

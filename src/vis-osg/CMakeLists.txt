cmake_minimum_required( VERSION 3.10 )

find_path( VIS_INCLUDE_DIR NAMES "vis/mesh.h" PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../include )

file ( GLOB VIS_INCLUDE_FILES "${VIS_INCLUDE_DIR}/vis/*.h" )
file ( GLOB VIS_OSG_INCLUDE_FILES "${VIS_INCLUDE_DIR}/vis-osg/*.h" )
file ( GLOB VIS_OSG_SOURCE_FILES "*.h" "*.cpp" )

add_library(vis-osg SHARED ${VIS_INCLUDE_FILES} ${VIS_OSG_SOURCE_FILES} ${VIS_OSG_INCLUDE_FILES})

# Require C++17 standard
set_target_properties(vis-osg PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# OpenSceneGraph
FIND_PACKAGE( OpenSceneGraph REQUIRED
  osg
  osgWidget
  osgQt
  osgGA
  osgViewer
  osgUtil
  osgDB
  osgShadow
  OpenThreads )

target_include_directories(vis-osg PUBLIC ${VIS_INCLUDE_DIR})
target_include_directories(vis-osg PRIVATE ${OSG_INCLUDE_DIR})
target_include_directories(vis-osg PRIVATE ${XO_INCLUDE_DIR})

target_link_libraries(vis-osg
	xo
	${OSG_LIBRARIES}
	${OSGWIDGET_LIBRARIES}
	${OSGGA_LIBRARIES}
	${OSGVIEWER_LIBRARIES}
	${OSGQT_LIBRARIES}
	${OSGDB_LIBRARIES}
	${OSGSHADOW_LIBRARIES}
	${OPENTHREADS_LIBRARIES}
	)

#include( PrecompiledHeaders )
#use_precompiled_headers( VIS_OSG_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h" "stdafx.cpp" 256 )

if (MSVC)
	target_precompile_headers(vis-osg PRIVATE
		<string> <vector> <algorithm> <memory> <limits> <fstream>
		<osg/Vec3f>	<osg/Vec4f> <osg/Quat> <osg/Group> <osg/Geode> <osg/Geometry> <osg/Material> <osg/PositionAttitudeTransform>
	)
	file (GLOB_RECURSE PRECOMPILED_HEADER_FILES ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cmake_pch.*)
	source_group("CMakePCH" FILES ${PRECOMPILED_HEADER_FILES})

	source_group("vis" FILES ${VIS_INCLUDE_FILES})
	source_group("vis-osg" FILES ${VIS_OSG_SOURCE_FILES} ${VIS_OSG_INCLUDE_FILES})
	target_compile_definitions(vis-osg PRIVATE VIS_EXPORTS)
	target_compile_options(vis-osg PRIVATE "/MP") # multithreaded compilation on MSVC
endif()

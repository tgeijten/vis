cmake_minimum_required( VERSION 3.12 )

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/CMakeModules")

project( vis )

find_path( VIS_INCLUDE_DIR NAMES "vis/mesh.h" PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include )
file ( GLOB VIS_INCLUDE_FILES "${VIS_INCLUDE_DIR}/vis/*.h" )

add_subdirectory( src/vis-osg )

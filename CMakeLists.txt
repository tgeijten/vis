cmake_minimum_required( VERSION 3.10 )

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/CMakeModules")

project( vis )

add_subdirectory( src/vis-osg )

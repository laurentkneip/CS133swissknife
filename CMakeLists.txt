cmake_minimum_required(VERSION 3.0)
project(swissknife)

#version number
set( SWISSKNIFE_VERSION_MAJOR 1 )
set( SWISSKNIFE_VERSION_MINOR 0 )

#set build type
set(CMAKE_BUILD_TYPE Debug)

#add path for find scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

#find libraries

#configure a header file to pass CMake settings
configure_file(
  "${PROJECT_SOURCE_DIR}/swissknife_config.h.in"
  "${PROJECT_BINARY_DIR}/swissknife_config.h")

#add binary tree to search path so we can find swissknife_config.h
include_directories( "${PROJECT_BINARY_DIR}" )

#add directory with include files of this project
include_directories( "${PROJECT_SOURCE_DIR}/trunk/include" )

add_subdirectory( trunk )
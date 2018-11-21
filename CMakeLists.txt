cmake_minimum_required(VERSION 3.0.0)
project(cildhdi VERSION 0.1.0)

add_compile_options(-std=c++11)

find_package(snowhouse REQUIRED)
include_directories(${SNOWHOUSE_INCLUDE_DIR})
find_package(igloo REQUIRED)
include_directories(${IGLOO_INCLUDE_DIR})

add_subdirectory("LinkList")
add_subdirectory("Matrix")
add_subdirectory("String")
add_subdirectory("ga-de-ry-po-lu-ki-cypher-vol-2")
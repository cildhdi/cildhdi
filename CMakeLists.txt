cmake_minimum_required(VERSION 3.0.0)
project(cildhdi VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_subdirectory("LinkList")
add_subdirectory("Matrix")
add_subdirectory("String")
add_subdirectory("Course")
add_subdirectory("codewars")
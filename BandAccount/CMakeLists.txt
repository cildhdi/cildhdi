cmake_minimum_required(VERSION 3.0.0)
project(BankAccount VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
include_directories(include lib)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE TEST_SRC tests/*.cpp)

add_executable(BankAccountTest ${TEST_SRC} ${SRC})

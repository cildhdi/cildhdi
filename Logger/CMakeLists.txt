cmake_minimum_required(VERSION 3.0.0)

project(Logger VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

add_library(Logger Logger.cpp)

find_package(GTest REQUIRED)

if(GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIR})
    include_directories(${PROJECT_SOURCE_DIR})
    add_executable(LoggerTest test/test.cpp)
    target_link_libraries(LoggerTest GTest::GTest Logger)
endif(GTEST_FOUND)

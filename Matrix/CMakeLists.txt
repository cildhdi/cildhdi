add_compile_options(-std=c++14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(Matrix_unittest Matrix_unittest.cpp)
target_link_libraries(Matrix_unittest ${GTEST_LIBRARY} pthread)
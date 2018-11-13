add_compile_options(-std=c++11)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(String_unittest String_unittest.cpp)
target_link_libraries(String_unittest ${GTEST_LIBRARY} pthread)
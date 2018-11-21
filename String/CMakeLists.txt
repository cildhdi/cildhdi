add_executable(String_unittest String_unittest.cpp)
target_link_libraries(String_unittest ${GTEST_LIBRARY} pthread)
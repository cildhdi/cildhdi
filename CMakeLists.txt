cmake_minimum_required(VERSION 3.0.0)
project(cildhdi VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

enable_testing()
# single file's build and test
macro(sfbt file_path btest)
    string(REPLACE "/" "." target_name ${file_path})
    string(REPLACE ":" "." target_name ${target_name})
    add_executable(${target_name} ${file_path})
    if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        target_link_libraries(${target_name} m)
    endif()
    if(${btest})
        add_test(${target_name} ${target_name})        
    endif()
endmacro()

add_subdirectory(LinkList)
add_subdirectory(Matrix)
add_subdirectory("String")
add_subdirectory(Course)
add_subdirectory(Logger)
add_subdirectory(codewars)
add_subdirectory(EducationalAdministration)
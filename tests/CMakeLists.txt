cmake_minimum_required(VERSION 3.15...4.00)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ccalculator_test
        LANGUAGES C CXX)

add_executable(ccalculator_tests ccalculator_tests.cpp operations.cpp)
target_include_directories(ccalculator_tests PRIVATE ../include)

file(GLOB src_files ../src/*.c)
add_library(src STATIC ${src_files})
target_include_directories(src PRIVATE ../include)

find_package(GTest REQUIRED)

enable_testing()

target_link_libraries(ccalculator_tests GTest::gtest src)

cmake_minimum_required(VERSION 3.15...4.00)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ccalculator_test
        LANGUAGES C CXX)

add_executable(ccalculator_tests ccalculator_tests.cpp)

add_library(tests STATIC operations.cpp)
target_include_directories(tests PRIVATE ../include)

add_library(src_files STATIC ../src/*.c)
target_include_directories(src_files PRIVATE ../include)

find_package(GTest REQUIRED)

enable_testing()

target_link_libraries(ccalculator_tests GTest::gtest_main src_files)

gtest_discover_tests(ccalculator_tests)

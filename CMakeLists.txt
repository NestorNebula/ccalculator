cmake_minimum_required(VERSION 3.15...4.00)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ccalculator
        VERSION 0.0.0
        DESCRIPTION "A command line calculator"
        LANGUAGES C CXX)

file(GLOB src_code src/*.c)

add_executable(ccalculator ${src_code})
target_include_directories(ccalculator PRIVATE include)

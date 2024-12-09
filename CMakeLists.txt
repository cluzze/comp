cmake_minimum_required(VERSION 3.10)
project(comp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(cc main.cpp src/lexer.cpp)
target_include_directories(cc PUBLIC include)
target_compile_features(cc PRIVATE cxx_std_20)
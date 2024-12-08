cmake_minimum_required(VERSION 3.10)
project(comp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


include_directories(include)

add_executable(cc main.cpp src/lexer.cpp)
target_compile_features(cc PRIVATE cxx_std_20)



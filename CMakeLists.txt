cmake_minimum_required(VERSION 3.23)

project(rt)

add_library(rt STATIC)

target_include_directories(rt PUBLIC include)

target_compile_features(rt PRIVATE cxx_std_17)

add_subdirectory(src)
add_subdirectory(examples)
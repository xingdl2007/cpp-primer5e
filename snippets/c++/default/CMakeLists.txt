cmake_minimum_required(VERSION 3.5)
add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_CXX_STANDARD 11)

add_executable(default main.cc)
target_compile_features(default PRIVATE cxx_range_for cxx_auto_type)

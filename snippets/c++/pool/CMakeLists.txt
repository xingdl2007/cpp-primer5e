cmake_minimum_required(VERSION 3.5)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(pool main.cc)
target_compile_features(pool PRIVATE cxx_range_for cxx_auto_type)

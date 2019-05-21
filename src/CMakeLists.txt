cmake_minimum_required(VERSION 3.9.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# pthread and prefer -pthread flag
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# set variables
set(CMAKE_CXX_FLAGS -Wall)

enable_testing()

add_subdirectory(chapter1)
add_subdirectory(chapter2)
add_subdirectory(chapter3)
add_subdirectory(chapter4)
add_subdirectory(chapter5)
add_subdirectory(chapter6)
add_subdirectory(chapter7)
add_subdirectory(chapter8)
add_subdirectory(chapter9)
add_subdirectory(chapter10)
add_subdirectory(chapter11)
add_subdirectory(chapter12)
add_subdirectory(chapter13)
add_subdirectory(chapter14)
add_subdirectory(chapter15)
add_subdirectory(chapter16)
add_subdirectory(chapter17)
add_subdirectory(chapter18)
add_subdirectory(chapter19)
add_subdirectory(concurrency)
add_subdirectory(network)
add_subdirectory(verify)
add_subdirectory(experiment)
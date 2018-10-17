cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "-fsanitize=thread -fPIE")
add_executable(demo main.cc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)
set(THREAD_PREFER_PTHREAD_FLAG ON)
target_link_libraries(demo Threads::Threads)

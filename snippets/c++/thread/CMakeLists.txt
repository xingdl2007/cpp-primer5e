cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra -Wpedantic)
add_executable(thread main.cc)

# which will give compiler -pthread option, ref GCC 8.2 Manual
set(THREADS_PREFER_PTHREAD_FLAG ON)  
find_package(Threads REQUIRED)
target_link_libraries(thread Threads::Threads)


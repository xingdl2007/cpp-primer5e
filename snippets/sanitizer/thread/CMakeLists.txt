cmake_minimum_required(VERSION 3.5)

# c++11 is required, which is not the case, just for practice
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# thread sanitizer check
set(CMAKE_CXX_FLAGS "-fsanitize=thread -fPIE -g")
add_executable(simple_race simple_race.cc)

# pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(simple_race Threads::Threads)


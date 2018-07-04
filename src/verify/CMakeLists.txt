project(verify)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(forward_declarations)
add_subdirectory(volatile)
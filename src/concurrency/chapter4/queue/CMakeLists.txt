# output
add_executable(queue queue.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(queue Threads::Threads)
# output
add_executable(queue2 queue.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(queue2 Threads::Threads)

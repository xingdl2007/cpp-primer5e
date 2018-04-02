# output
add_executable(queue4 queue.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(queue4 Threads::Threads)
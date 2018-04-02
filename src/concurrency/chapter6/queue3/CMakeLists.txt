# output
add_executable(queue3 queue.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(queue3 Threads::Threads)
# output
add_executable(queue5 queue.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(queue5 Threads::Threads)
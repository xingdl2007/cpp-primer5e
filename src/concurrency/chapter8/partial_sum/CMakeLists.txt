# output
add_executable(partial_sum partial_sum.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(partial_sum Threads::Threads)
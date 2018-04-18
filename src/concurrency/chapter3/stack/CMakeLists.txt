# output
add_executable(sample3 stack.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(sample3 Threads::Threads)
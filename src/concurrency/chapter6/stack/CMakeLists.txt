# output
add_executable(stack2 stack.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(stack2 Threads::Threads)
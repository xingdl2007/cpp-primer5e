# output
add_executable(thread_local thread_local.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(thread_local Threads::Threads)
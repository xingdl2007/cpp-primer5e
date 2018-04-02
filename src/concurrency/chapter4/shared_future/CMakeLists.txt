# output
add_executable(shared_future future.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(shared_future Threads::Threads)
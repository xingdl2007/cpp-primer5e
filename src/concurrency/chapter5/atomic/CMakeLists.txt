# output
add_executable(atomic atomic.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(atomic Threads::Threads)
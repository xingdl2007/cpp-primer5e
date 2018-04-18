# output
add_executable(simplest simplest.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(simplest Threads::Threads)
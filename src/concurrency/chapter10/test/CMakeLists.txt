# output
add_executable(multitest test.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(multitest Threads::Threads)
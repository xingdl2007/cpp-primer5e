# output
add_executable(for_each for_each.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(for_each Threads::Threads)
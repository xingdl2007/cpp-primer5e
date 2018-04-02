# output
add_executable(parallel_find find.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(parallel_find Threads::Threads)
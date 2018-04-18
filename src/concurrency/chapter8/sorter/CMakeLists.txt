# output
add_executable(sorter sorter.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(sorter Threads::Threads)
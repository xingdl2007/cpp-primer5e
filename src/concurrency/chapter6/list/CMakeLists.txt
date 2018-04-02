# output
add_executable(list list.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(list Threads::Threads)
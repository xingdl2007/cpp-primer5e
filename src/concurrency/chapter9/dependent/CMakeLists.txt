# output
add_executable(dependent dependent.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(dependent Threads::Threads)
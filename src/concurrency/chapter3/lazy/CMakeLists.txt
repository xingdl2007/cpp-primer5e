# output
add_executable(lazy sample.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(lazy Threads::Threads)
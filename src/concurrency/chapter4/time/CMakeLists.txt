# output
add_executable(time time.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(time Threads::Threads)
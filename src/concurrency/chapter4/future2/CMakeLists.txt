# output
add_executable(future2 future.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(future2 Threads::Threads)
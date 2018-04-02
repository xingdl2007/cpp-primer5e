# output
add_executable(local sample.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(local Threads::Threads)
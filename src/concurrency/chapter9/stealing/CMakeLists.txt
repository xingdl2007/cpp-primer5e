# output
add_executable(stealing stealing.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(stealing Threads::Threads)
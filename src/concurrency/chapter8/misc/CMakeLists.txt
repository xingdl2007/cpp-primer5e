# output
add_executable(misc8 misc.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(misc8 Threads::Threads)
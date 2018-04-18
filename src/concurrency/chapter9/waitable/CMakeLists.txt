# output
add_executable(waitable waitable.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(waitable Threads::Threads)
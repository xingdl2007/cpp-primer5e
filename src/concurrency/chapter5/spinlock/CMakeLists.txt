# output
add_executable(spinlock spinlock.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(spinlock Threads::Threads)
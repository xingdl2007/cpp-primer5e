# output
add_executable(interruptible interruptible.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(interruptible Threads::Threads)
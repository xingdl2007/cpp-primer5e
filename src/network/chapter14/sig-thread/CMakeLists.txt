add_executable(sig-thread sig-thread.c)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(sig-thread Threads::Threads)
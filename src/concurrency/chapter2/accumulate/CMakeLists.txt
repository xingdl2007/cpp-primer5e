# output
add_executable(accumulate accumulate.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(accumulate Threads::Threads)
# output
add_executable(qsort qsort.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(qsort Threads::Threads)
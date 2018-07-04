# output
add_executable(misc misc.cc Sales_data.h)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(misc Threads::Threads)
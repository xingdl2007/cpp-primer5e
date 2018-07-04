add_executable(volatile main.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(volatile Threads::Threads)
set(CMAKE_CXX_FLAGS "-O2 -g")
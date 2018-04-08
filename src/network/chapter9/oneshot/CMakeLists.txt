add_executable(oneshot oneshot.c)
target_link_libraries(oneshot Threads::Threads)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
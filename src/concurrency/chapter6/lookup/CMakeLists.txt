# output
find_package(Boost COMPONENTS thread REQUIRED)
add_executable(lookup lookup_table.cc)
target_link_libraries(lookup ${Boost_LIBRARIES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

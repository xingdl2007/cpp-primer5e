# output
include_directories(../sales)
add_executable(average average.cc ../sales/Sales_data.cc ../sales/Sales_data.h)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
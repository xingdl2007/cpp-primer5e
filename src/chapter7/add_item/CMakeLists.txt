# output
include_directories(../sales)
add_executable(add_item2 add.cc ../sales/Sales_data.cc ../sales/Sales_data.h)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
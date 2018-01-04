# add include
include_directories(../include)

# output
add_executable(add_item  add_item.cc ../include/Sales_item.h)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

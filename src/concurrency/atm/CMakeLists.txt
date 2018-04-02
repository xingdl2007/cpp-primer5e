# output
PROJECT(atm CXX)
add_executable(atm main.cc atm.h bank.h dispatcher.h interface.h logic.h queue.h receiver.h sender.h template.h)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
target_link_libraries(atm Threads::Threads)
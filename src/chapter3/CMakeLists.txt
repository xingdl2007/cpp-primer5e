project(CHAPTER3 CXX)

# set variables
set(CXX_FLAGS -g -Wall -march=native -rdynamic -std=c++11)

# add subdirectory
add_subdirectory(sales2)
add_subdirectory(read)
add_subdirectory(char)
add_subdirectory(vector)
add_subdirectory(iterator)
add_subdirectory(array)
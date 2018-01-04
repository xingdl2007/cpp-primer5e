project(CHAPTER1 CXX)

# set variables
set(CXX_FLAGS -g -Wall -march=native -rdynamic -std=c++11)

add_subdirectory(main)
add_subdirectory(hello)
add_subdirectory(add)
add_subdirectory(mul)
add_subdirectory(sum)
add_subdirectory(add_item)
add_subdirectory(occurs)
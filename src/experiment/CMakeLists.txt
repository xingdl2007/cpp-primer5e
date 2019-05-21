# function_name, test file, 3rd dependencies
function(awesomedb_test test_file depends)
    get_filename_component(test_target_name "${test_file}" NAME_WE)
    add_executable("${test_target_name}" "${test_file}")
    target_link_libraries("${test_target_name}" "${depends}")
    add_test(NAME "${test_target_name}" COMMAND "${test_target_name}")
endfunction()

# will halt whole system
# awesomedb_test("new.cc" "")

# optional: for verification
# objdump -d reordering.out > reordering.s
awesomedb_test("reordering.cc" "Threads::Threads") 
awesomedb_test("appleveldb.cc" "leveldb")
awesomedb_test("template.cc" "")
awesomedb_test("hashtest.cc" "")
awesomedb_test("static.cc" "")
awesomedb_test("cpp11.cc" "")
awesomedb_test("nmc.c" "")
awesomedb_test("nmcc.cc" "")
awesomedb_test("conditional.cc" "Threads::Threads")
awesomedb_test("crtp.cc" "")
awesomedb_test("valuecatogery.cc" "")
awesomedb_test("pod.cc" "")
awesomedb_test("locale.cc" "")
awesomedb_test("typetraits.cc" "")
awesomedb_test("atomictest.cc" "")
awesomedb_test("unordered.cc" "Threads::Threads")
awesomedb_test("relaxed.cc" "Threads::Threads")
awesomedb_test("transitive.cc" "Threads::Threads")
awesomedb_test("transitive2.cc" "Threads::Threads")
awesomedb_test("consume.cc" "Threads::Threads")
awesomedb_test("release_sequence.cc" "Threads::Threads")
awesomedb_test("fences.cc" "Threads::Threads")
awesomedb_test("file.cc" "")
awesomedb_test("clock.cc" "")
awesomedb_test("timetest.cc" "")
awesomedb_test("plugin.cc" ${CMAKE_DL_LIBS})
awesomedb_test("asm.cc" "")

# multicast example
add_executable(mcastclient mcastclient.c)
add_executable(mcastserver mcastserver.c)

add_library(plugin_hello "plugin_hello.cc")
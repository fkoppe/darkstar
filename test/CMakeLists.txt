macro(dark_test_add filename)
   add_executable(${filename} ${filename}.c)
   target_link_libraries(${filename} PRIVATE darkstar)
   add_test(NAME ${filename} COMMAND $<TARGET_FILE:${filename}>)
endmacro(dark_test_add)

dark_test_add(test_test)

#core_module
add_subdirectory(core)

macro(dark_test_add filename)
   add_executable(${filename} ${filename}.c)
   target_link_libraries(${filename} PRIVATE darkstar)
   add_test(NAME ${filename} COMMAND $<TARGET_FILE:${filename}>)
endmacro(dark_test_add)

dark_test_add(test_test)

#-----

add_subdirectory(core)

#-----

add_subdirectory(hash)
add_subdirectory(math)
add_subdirectory(memory)

#-----

add_subdirectory(container)
add_subdirectory(platform)

#-----

add_subdirectory(algorithm)
add_subdirectory(stream)

#-----

add_subdirectory(char)

#-----

add_subdirectory(random)
add_subdirectory(time)
#add_subdirectory(log)

#-----

#add_subdirectory(ecs)
#add_subdirectory(window)

#-----

#add_subdirectory(renderer)

#-----

target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/darkstar.h
    ${CMAKE_CURRENT_LIST_DIR}/info.h
)

add_subdirectory(char)
add_subdirectory(container)
add_subdirectory(core)
add_subdirectory(hash)
add_subdirectory(math)
add_subdirectory(order)
add_subdirectory(profile)
add_subdirectory(random)

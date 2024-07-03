target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/darkstar.h
)

add_subdirectory(container)
add_subdirectory(core)
add_subdirectory(memory)

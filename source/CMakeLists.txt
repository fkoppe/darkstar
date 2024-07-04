target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/dark_library.h
    ${CMAKE_CURRENT_LIST_DIR}/darktest.c
)

target_precompile_headers(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/dark_library.h
)

add_subdirectory(container)
add_subdirectory(core)
add_subdirectory(math)
add_subdirectory(memory)

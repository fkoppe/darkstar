target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/dark_library.h
)

target_precompile_headers(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/dark_library.h
)

add_subdirectory(char)
add_subdirectory(container)
add_subdirectory(core)
add_subdirectory(math)
add_subdirectory(profile)

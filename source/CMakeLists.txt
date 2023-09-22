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

add_subdirectory(core)
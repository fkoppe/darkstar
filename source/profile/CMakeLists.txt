target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/allocation_override.h
    ${CMAKE_CURRENT_LIST_DIR}/memory_profiler.c
    ${CMAKE_CURRENT_LIST_DIR}/profile_module.h
)

target_precompile_headers(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/allocation_override.h
)

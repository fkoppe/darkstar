target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/allocation_override.h
    ${CMAKE_CURRENT_LIST_DIR}/debug_helper.c
    ${CMAKE_CURRENT_LIST_DIR}/debug_helper.h
    ${CMAKE_CURRENT_LIST_DIR}/debug_memory.c
    ${CMAKE_CURRENT_LIST_DIR}/debug_module.h
    ${CMAKE_CURRENT_LIST_DIR}/debug_print.c
)

target_precompile_headers(
    darkstar
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/allocation_override.h
)

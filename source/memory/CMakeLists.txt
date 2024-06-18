target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/allocator_override.h
    ${CMAKE_CURRENT_LIST_DIR}/allocator.c
    ${CMAKE_CURRENT_LIST_DIR}/memory_debug_helper.c
    ${CMAKE_CURRENT_LIST_DIR}/memory_debug_helper.h
    ${CMAKE_CURRENT_LIST_DIR}/memory_debug.c
    ${CMAKE_CURRENT_LIST_DIR}/memory_module.h
    ${CMAKE_CURRENT_LIST_DIR}/os_allocator.c
)

target_precompile_headers(
    darkstar
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/allocator_override.h
)

target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/allocator.c
    ${CMAKE_CURRENT_LIST_DIR}/memory_module.h
    ${CMAKE_CURRENT_LIST_DIR}/os_allocator.c
)

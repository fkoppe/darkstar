target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/entropy.c
    ${CMAKE_CURRENT_LIST_DIR}/random_module.h
    ${CMAKE_CURRENT_LIST_DIR}/splitmix.c
    ${CMAKE_CURRENT_LIST_DIR}/uuid4.c
)

target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/entropy.h
    ${CMAKE_CURRENT_LIST_DIR}/random.h
    ${CMAKE_CURRENT_LIST_DIR}/splitmix.h
    ${CMAKE_CURRENT_LIST_DIR}/uuid4.h
)

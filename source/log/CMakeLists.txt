target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/log_module.h
    ${CMAKE_CURRENT_LIST_DIR}/logger.c
    ${CMAKE_CURRENT_LIST_DIR}/logger_helper.c
    ${CMAKE_CURRENT_LIST_DIR}/logger_helper.h
)

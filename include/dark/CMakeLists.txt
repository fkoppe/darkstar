target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/darkstar.h
    ${CMAKE_CURRENT_LIST_DIR}/info.h
)

add_subdirectory(core)

target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/container_helper.h
    ${CMAKE_CURRENT_LIST_DIR}/container_module.h
	${CMAKE_CURRENT_LIST_DIR}/darray.c
	${CMAKE_CURRENT_LIST_DIR}/vector.c
)

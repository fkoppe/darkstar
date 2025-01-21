target_sources(
    darkstar
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/geometry_module.h
    ${CMAKE_CURRENT_LIST_DIR}/mat3_f.c
	${CMAKE_CURRENT_LIST_DIR}/vec2_f.c
    ${CMAKE_CURRENT_LIST_DIR}/vec3_f.c
)

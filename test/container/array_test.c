#include "dark/container/array.h"
#include <dark/darkstar.h>
#include <stdlib.h>

int main()
{

#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    void* array = malloc(dark_array_struct_size());
    dark_array_create_size(array, sizeof(int), 10, 10);
    dark_array_destroy(array);
    free(array);

    void* array_del = dark_array_new_size(sizeof(int), 55, 22);
    dark_array_delete(array_del);

    void* array_1 = dark_array_new(sizeof(int));
    void* array_2 = dark_array_new_capacity(sizeof(int), 10);
    void* array_3 = dark_array_new_size(sizeof(int), 10, 2);

    DARK_ARRAY_AT(array_3, 0, int) = 42;
    DARK_ARRAY_AT(array_3, 1, int) = 99;

    DARK_TEST_EQ_I(42, DARK_ARRAY_FRONT(array_3, int));
    DARK_TEST_EQ_I(99, DARK_ARRAY_BACK(array_3, int));
    DARK_TEST_EQ_I(*DARK_ARRAY_DATA(array_3, int), DARK_ARRAY_FRONT(array_3, int));

    void* null = NULL;
    void* result = dark_array_emplace(array_1, 0, 0);
    DARK_TEST_EQ_M(&result, &null , sizeof(void*));

    int integer = 8;
    dark_array_push_back(array_1, &integer);
    dark_array_push_back(array_2, &integer);
    dark_array_push_back(array_3, &integer);

    DARK_TEST_EQ_I(DARK_ARRAY_FRONT(array_1, int), DARK_ARRAY_BACK(array_1, int));
    DARK_TEST_EQ_I(DARK_ARRAY_FRONT(array_2, int), DARK_ARRAY_BACK(array_2, int));

    DARK_TEST_EQ_I(8, DARK_ARRAY_FRONT(array_1, int));
    DARK_TEST_EQ_I(8, DARK_ARRAY_FRONT(array_2, int));

    DARK_TEST_EQ_I(42, DARK_ARRAY_FRONT(array_3, int));
    DARK_TEST_EQ_I(8, DARK_ARRAY_BACK(array_3, int));

    DARK_TEST_EQ_U(1, dark_array_capacity(array_1));
    DARK_TEST_EQ_U(10, dark_array_capacity(array_2));
    DARK_TEST_EQ_U(10, dark_array_capacity(array_3));
    DARK_TEST_EQ_U(1, dark_array_size(array_1));
    DARK_TEST_EQ_U(1, dark_array_size(array_2));
    DARK_TEST_EQ_U(3, dark_array_size(array_3));

    dark_array_delete(array_1);
    dark_array_delete(array_2);
    dark_array_delete(array_3);

    array_1 = dark_array_new(sizeof(int));
    dark_array_push_front(array_1, &integer);
    dark_array_delete(array_1);

    array_1 = dark_array_new_size(sizeof(int), 10, 10);

    dark_array_insert(array_1, 1, &integer);
    DARK_TEST_EQ_I(8, DARK_ARRAY_AT(array_1, 1, int));

    dark_array_delete(array_1);

    int arr[2] = { 33, 44 };
    array_1 = dark_array_new_size(sizeof(int), 10, 10);

    dark_array_push(array_1, 5, 2, arr);

    DARK_TEST_EQ_I(33, DARK_ARRAY_AT(array_1, 5, int));
    DARK_TEST_EQ_I(44, DARK_ARRAY_AT(array_1, 6, int));

    dark_array_delete(array_1);

    int arr2[4] = { 13, 14, 55, 99 };
    array_1 = dark_array_new(sizeof(int));

    dark_array_push(array_1, 0, 2, arr);
    dark_array_push(array_1, 0, 2, arr2);
    dark_array_push(array_1, 0, 4, arr2);

    DARK_TEST_EQ_U(8, dark_array_capacity(array_1));
    DARK_TEST_EQ_U(8, dark_array_size(array_1));

    DARK_TEST_EQ_I(13, DARK_ARRAY_AT(array_1, 0, int));
    DARK_TEST_EQ_I(14, DARK_ARRAY_AT(array_1, 1, int));
    DARK_TEST_EQ_I(55, DARK_ARRAY_AT(array_1, 2, int));
    DARK_TEST_EQ_I(99, DARK_ARRAY_AT(array_1, 3, int));
    DARK_TEST_EQ_I(13, DARK_ARRAY_AT(array_1, 4, int));
    DARK_TEST_EQ_I(14, DARK_ARRAY_AT(array_1, 5, int));
    DARK_TEST_EQ_I(33, DARK_ARRAY_AT(array_1, 6, int));
    DARK_TEST_EQ_I(44, DARK_ARRAY_AT(array_1, 7, int));

    dark_array_pop_back(array_1);

    DARK_TEST_EQ_U(8, dark_array_capacity(array_1));
    DARK_TEST_EQ_U(7, dark_array_size(array_1));

    dark_array_pop(array_1, 0, 2);

    DARK_TEST_EQ_U(8, dark_array_capacity(array_1));
    DARK_TEST_EQ_U(5, dark_array_size(array_1));

    dark_array_shrink_to_fit(array_1);

    DARK_TEST_EQ_U(5, dark_array_capacity(array_1));
    DARK_TEST_EQ_U(5, dark_array_size(array_1));

    dark_array_reserve_exact(array_1, 22);

    DARK_TEST_EQ_U(22, dark_array_capacity(array_1));
    DARK_TEST_EQ_U(5, dark_array_size(array_1));

    dark_array_shrink_to_fit(array_1);

    DARK_TEST_EQ_U(5, dark_array_capacity(array_1));
    DARK_TEST_EQ_U(5, dark_array_size(array_1));

    dark_array_resize(array_1, 6);

    DARK_TEST_EQ_U(6, dark_array_capacity(array_1));
    DARK_TEST_EQ_U(6, dark_array_size(array_1));

    dark_array_resize(array_1, 5);

    DARK_TEST_EQ_U(6, dark_array_capacity(array_1));
    DARK_TEST_EQ_U(5, dark_array_size(array_1));

    dark_array_clear(array_1);

    DARK_TEST_EQ_U(6, dark_array_capacity(array_1));
    DARK_TEST_EQ_U(0, dark_array_size(array_1));

    DARK_TEST_EQ_U(sizeof(int), dark_array_element_size(array_1));

    dark_array_delete(array_1);

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}

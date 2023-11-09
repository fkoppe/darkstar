#include <dark/darkstar.h>

int main()
{

#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    void* darray_del = dark_darray_new_size(sizeof(int), 55, 22);
    dark_darray_delete(darray_del);

    void* darray_1 = dark_darray_new(sizeof(int));
    void* darray_2 = dark_darray_new_capacity(sizeof(int), 10);
    void* darray_3 = dark_darray_new_size(sizeof(int), 10, 2);

    DARK_DARRAY_AT(darray_3, 0, int) = 42;
    DARK_DARRAY_AT(darray_3, 1, int) = 99;

    DARK_TEST_EQ_I(42, DARK_DARRAY_FRONT(darray_3, int));
    DARK_TEST_EQ_I(99, DARK_DARRAY_BACK(darray_3, int));
    DARK_TEST_EQ_I(*DARK_DARRAY_DATA(darray_3, int), DARK_DARRAY_FRONT(darray_3, int));

    int integer = 8;
    dark_darray_push_back(darray_1, &integer);
    dark_darray_push_back(darray_2, &integer);
    dark_darray_push_back(darray_3, &integer);

    DARK_TEST_EQ_I(DARK_DARRAY_FRONT(darray_1, int), DARK_DARRAY_BACK(darray_1, int));
    DARK_TEST_EQ_I(DARK_DARRAY_FRONT(darray_2, int), DARK_DARRAY_BACK(darray_2, int));

    DARK_TEST_EQ_I(8, DARK_DARRAY_FRONT(darray_1, int));
    DARK_TEST_EQ_I(8, DARK_DARRAY_FRONT(darray_2, int));

    DARK_TEST_EQ_I(42, DARK_DARRAY_FRONT(darray_3, int));
    DARK_TEST_EQ_I(8, DARK_DARRAY_BACK(darray_3, int));

    DARK_TEST_EQ_U(1, dark_darray_capacity(darray_1));
    DARK_TEST_EQ_U(10, dark_darray_capacity(darray_2));
    DARK_TEST_EQ_U(10, dark_darray_capacity(darray_3));
    DARK_TEST_EQ_U(1, dark_darray_size(darray_1));
    DARK_TEST_EQ_U(1, dark_darray_size(darray_2));
    DARK_TEST_EQ_U(3, dark_darray_size(darray_3));

    dark_darray_delete(darray_1);
    dark_darray_delete(darray_2);
    dark_darray_delete(darray_3);

    darray_1 = dark_darray_new(sizeof(int));
    dark_darray_push_front(darray_1, &integer);
    dark_darray_delete(darray_1);

    darray_1 = dark_darray_new_size(sizeof(int), 10, 10);

    dark_darray_insert(darray_1, 1, &integer);
    DARK_TEST_EQ_I(8, DARK_DARRAY_AT(darray_1, 1, int));

    dark_darray_delete(darray_1);

    int arr[2] = { 33, 44 };
    darray_1 = dark_darray_new_size(sizeof(int), 10, 10);

    dark_darray_push(darray_1, 5, 2, arr);

    DARK_TEST_EQ_I(33, DARK_DARRAY_AT(darray_1, 5, int));
    DARK_TEST_EQ_I(44, DARK_DARRAY_AT(darray_1, 6, int));

    dark_darray_delete(darray_1);

    int arr2[4] = { 13, 14, 55, 99 };
    darray_1 = dark_darray_new(sizeof(int));

    dark_darray_push(darray_1, 0, 2, arr);
    dark_darray_push(darray_1, 0, 2, arr2);
    dark_darray_push(darray_1, 0, 4, arr2);

    DARK_TEST_EQ_U(8, dark_darray_capacity(darray_1));
    DARK_TEST_EQ_U(8, dark_darray_size(darray_1));

    DARK_TEST_EQ_I(13, DARK_DARRAY_AT(darray_1, 0, int));
    DARK_TEST_EQ_I(14, DARK_DARRAY_AT(darray_1, 1, int));
    DARK_TEST_EQ_I(55, DARK_DARRAY_AT(darray_1, 2, int));
    DARK_TEST_EQ_I(99, DARK_DARRAY_AT(darray_1, 3, int));
    DARK_TEST_EQ_I(13, DARK_DARRAY_AT(darray_1, 4, int));
    DARK_TEST_EQ_I(14, DARK_DARRAY_AT(darray_1, 5, int));
    DARK_TEST_EQ_I(33, DARK_DARRAY_AT(darray_1, 6, int));
    DARK_TEST_EQ_I(44, DARK_DARRAY_AT(darray_1, 7, int));

    dark_darray_pop_back(darray_1);

    DARK_TEST_EQ_U(8, dark_darray_capacity(darray_1));
    DARK_TEST_EQ_U(7, dark_darray_size(darray_1));

    dark_darray_pop(darray_1, 0, 2);

    DARK_TEST_EQ_U(8, dark_darray_capacity(darray_1));
    DARK_TEST_EQ_U(5, dark_darray_size(darray_1));

    dark_darray_shrink_to_fit(darray_1);

    DARK_TEST_EQ_U(5, dark_darray_capacity(darray_1));
    DARK_TEST_EQ_U(5, dark_darray_size(darray_1));

    dark_darray_reserve_exact(darray_1, 22);

    DARK_TEST_EQ_U(22, dark_darray_capacity(darray_1));
    DARK_TEST_EQ_U(5, dark_darray_size(darray_1));

    dark_darray_shrink_to_fit(darray_1);

    DARK_TEST_EQ_U(5, dark_darray_capacity(darray_1));
    DARK_TEST_EQ_U(5, dark_darray_size(darray_1));

    dark_darray_resize(darray_1, 6);

    DARK_TEST_EQ_U(6, dark_darray_capacity(darray_1));
    DARK_TEST_EQ_U(6, dark_darray_size(darray_1));

    dark_darray_resize(darray_1, 5);

    DARK_TEST_EQ_U(6, dark_darray_capacity(darray_1));
    DARK_TEST_EQ_U(5, dark_darray_size(darray_1));

    dark_darray_clear(darray_1);

    DARK_TEST_EQ_U(6, dark_darray_capacity(darray_1));
    DARK_TEST_EQ_U(0, dark_darray_size(darray_1));

    DARK_TEST_EQ_U(sizeof(int), dark_darray_element_size(darray_1));

    dark_darray_delete(darray_1);

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}

#include <dark/darkstar.h>

int main()
{
    #if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    void* vector = malloc(dark_vector_struct_size());
    dark_vector_create_size(vector, DARK_GROWTH_STANDARD, sizeof(int), 10, 10);
    dark_vector_destroy(vector);
    free(vector);

    void* vector_del = dark_vector_new(DARK_GROWTH_STANDARD, sizeof(int));
    dark_vector_delete(vector_del);

    vector_del = dark_vector_new_capacity(DARK_GROWTH_STANDARD, sizeof(int), 10);
    dark_vector_delete(vector_del);

    vector_del = dark_vector_new_size(DARK_GROWTH_STANDARD, sizeof(int), 10, 2);
    dark_vector_delete(vector_del);

    void* vector_test = dark_vector_new(DARK_GROWTH_STANDARD, sizeof(int));

    int i = 19;

    DARK_TEST_EQ_U(0, dark_vector_capacity(vector_test));
    dark_vector_push_back(vector_test, &i);
    DARK_TEST_EQ_U(1, dark_vector_capacity(vector_test));

    dark_vector_reserve(vector_test, 10);
    DARK_TEST_EQ_U(10, dark_vector_capacity(vector_test));

    dark_vector_reserve(vector_test, 12);
    DARK_TEST_EQ_U(15, dark_vector_capacity(vector_test));

    dark_vector_reserve(vector_test, 10);
    DARK_TEST_EQ_U(15, dark_vector_capacity(vector_test));

    dark_vector_resize(vector_test, 30);
    DARK_TEST_EQ_U(36, dark_vector_capacity(vector_test));
    DARK_TEST_EQ_U(30, dark_vector_size(vector_test));

    dark_vector_reserve_exact(vector_test, 30);
    DARK_TEST_EQ_U(30, dark_vector_capacity(vector_test));

    dark_vector_reserve_exact(vector_test, 31);
    DARK_TEST_EQ_U(31, dark_vector_capacity(vector_test));

    dark_vector_delete(vector_test);

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}

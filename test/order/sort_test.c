#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    int32_t arr_1[] = {2, 1, 3, 4, 2};
    int32_t arr_2[] = {1, 2, 3};

    DARK_TEST(!dark_sort_is(sizeof(int32_t), 5, arr_1, (Dark_Compare)dark_compare_i32));
    DARK_TEST(dark_sort_is(sizeof(int32_t), 3, arr_2, (Dark_Compare)dark_compare_i32));

    dark_sort_insertion(sizeof(int32_t), 5, arr_1, (Dark_Compare)dark_compare_i32);
    dark_sort_insertion(sizeof(int32_t), 3, arr_2, (Dark_Compare)dark_compare_i32);

    DARK_TEST(dark_sort_is(sizeof(int32_t), 5, arr_1, (Dark_Compare)dark_compare_i32));
    DARK_TEST(dark_sort_is(sizeof(int32_t), 3, arr_2, (Dark_Compare)dark_compare_i32));

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}

#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    //----------TEST----------
    DARK_TEST("sort_is")
    {
        int32_t arr_1[] = {2, 1, 3, 4, 2};
        int32_t arr_2[] = {1, 2, 3};

        DARK_TEST_FALSE(dark_sort_is(sizeof(int32_t), 5, arr_1, (Dark_Compare)dark_compare_i32));
        DARK_TEST_TRUE(dark_sort_is(sizeof(int32_t), 3, arr_2, (Dark_Compare)dark_compare_i32));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("sort_insertion")
    {
        int32_t arr_1[] = {2, 1, 3, 4, 2};
        int32_t arr_2[] = {1, 2, 3};

        dark_sort_insertion(sizeof(int32_t), 5, arr_1, (Dark_Compare)dark_compare_i32);
        dark_sort_insertion(sizeof(int32_t), 3, arr_2, (Dark_Compare)dark_compare_i32);

        DARK_TEST_TRUE(dark_sort_is(sizeof(int32_t), 5, arr_1, (Dark_Compare)dark_compare_i32));
        DARK_TEST_TRUE(dark_sort_is(sizeof(int32_t), 3, arr_2, (Dark_Compare)dark_compare_i32));
    }
    //--------------------------

    dark_test_end();

#if defined(___DARK_DEBUG)
    DARK_TEST_FALSE(dark_memory_profile_leak_is());

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}

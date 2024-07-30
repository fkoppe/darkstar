#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("sort_is")
    {
        int32_t buf_1[] = {2, 1, 3, 4, 2};
        int32_t buf_2[] = {1, 2, 3};

        const Dark_Array_View arr_1 = { buf_1, 5, sizeof(int32_t) };
        const Dark_Array_View arr_2 = { buf_2, 3, sizeof(int32_t) };

        DARK_TEST_FALSE(dark_sort_is(arr_1, (Dark_Compare)dark_compare_i32));
        DARK_TEST_TRUE(dark_sort_is(arr_2, (Dark_Compare)dark_compare_i32));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("sort_insertion")
    {
        int32_t buf_1[] = {2, 1, 3, 4, 2};
        int32_t buf_2[] = {1, 2, 3};

        const Dark_Array arr_1 = { buf_1, 5, sizeof(int32_t) };
        const Dark_Array arr_2 = { buf_2, 3, sizeof(int32_t) };

        int32_t element_buffer;

        dark_sort_insertion(arr_1, (Dark_Compare)dark_compare_i32, &element_buffer);
        dark_sort_insertion(arr_2, (Dark_Compare)dark_compare_i32, &element_buffer);

        DARK_TEST_TRUE(dark_sort_is(dark_array_view(arr_1), (Dark_Compare)dark_compare_i32));
        DARK_TEST_TRUE(dark_sort_is(dark_array_view(arr_2), (Dark_Compare)dark_compare_i32));
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

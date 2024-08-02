#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("find_linear_index")
    {
        int32_t buf_1[] = {2, 1, 3, 4, 2};
        int32_t buf_2[] = {1, 2, 3};
        int32_t buf_3[] = {1, 1, 3, 4, 2};

        const Dark_Array_View arr_1 = { sizeof(int32_t), 5, buf_1 };
        const Dark_Array_View arr_2 = { sizeof(int32_t), 3, buf_2 };
        const Dark_Array_View arr_3 = { sizeof(int32_t), 5, buf_3 };

        size_t index = 0;
        const int32_t element = 2;


        DARK_TEST_TRUE(dark_find_linear_index(&element, arr_1, (Dark_Compare)dark_compare_i32, &index));
        DARK_TEST_EQ_U(0, index);

        DARK_TEST_TRUE(dark_find_linear_index(&element, arr_2, (Dark_Compare)dark_compare_i32, &index));
        DARK_TEST_EQ_U(1, index);

        DARK_TEST_TRUE(dark_find_linear_index(&element, arr_3, (Dark_Compare)dark_compare_i32, &index));
        DARK_TEST_EQ_U(4, index);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("find_linear_index")
    {
        int32_t buf_1[] = {2, 1, 3, 4, 2};
        int32_t buf_2[] = {1, 2, 3};
        int32_t buf_3[] = {1, 1, 3, 4, 2};

        const Dark_Array_View arr_1 = { sizeof(int32_t), 5, buf_1 };
        const Dark_Array_View arr_2 = { sizeof(int32_t), 3, buf_2 };
        const Dark_Array_View arr_3 = { sizeof(int32_t), 5, buf_3 };

        size_t index = 0;
        const int32_t element = 2;


        DARK_TEST_TRUE(dark_find_linear_reverse_index(&element, arr_1, (Dark_Compare)dark_compare_i32, &index));
        DARK_TEST_EQ_U(4, index);

        DARK_TEST_TRUE(dark_find_linear_reverse_index(&element, arr_2, (Dark_Compare)dark_compare_i32, &index));
        DARK_TEST_EQ_U(1, index);

        DARK_TEST_TRUE(dark_find_linear_reverse_index(&element, arr_3, (Dark_Compare)dark_compare_i32, &index));
        DARK_TEST_EQ_U(4, index);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("find_binary_index")
    {
        int32_t buf_1[] = {1, 2, 3};
        int32_t buf_2[] = {2, 3, 4, 5, 6};

        const Dark_Array_View arr_1 = { sizeof(int32_t), 3, buf_1 };
        const Dark_Array_View arr_2 = { sizeof(int32_t), 5, buf_2 };

        size_t index = 0;
        const int32_t element = 2;


        DARK_TEST_TRUE(dark_find_binary_index(&element, arr_1, (Dark_Compare)dark_compare_i32, &index));
        DARK_TEST_EQ_U(1, index);

        DARK_TEST_TRUE(dark_find_binary_index(&element, arr_2, (Dark_Compare)dark_compare_i32, &index));
        DARK_TEST_EQ_U(0, index);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("find_linear")
    {
        int32_t buf_1[] = {2, 1, 3, 4, 2};
        int32_t buf_2[] = {1, 2, 3};
        int32_t buf_3[] = {1, 1, 3, 4, 2};

        const Dark_Array arrv_1 = { sizeof(int32_t), 5, buf_1 };
        const Dark_Array arrv_2 = { sizeof(int32_t), 3, buf_2 };
        const Dark_Array arrv_3 = { sizeof(int32_t), 5, buf_3 };

        const int32_t element = 2;


        DARK_TEST_EQ_P(dark_find_linear(&element, arrv_1, (Dark_Compare)dark_compare_i32), buf_1 + 0);

        DARK_TEST_EQ_P(dark_find_linear(&element, arrv_2, (Dark_Compare)dark_compare_i32), buf_2 + 1);

        DARK_TEST_EQ_P(dark_find_linear(&element, arrv_3, (Dark_Compare)dark_compare_i32), buf_3 + 4);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("find_linear_reverse")
    {
        int32_t buf_1[] = {2, 1, 3, 4, 2};
        int32_t buf_2[] = {1, 2, 3};
        int32_t buf_3[] = {1, 1, 3, 4, 2};

        const Dark_Array arrv_1 = { sizeof(int32_t), 5, buf_1 };
        const Dark_Array arrv_2 = { sizeof(int32_t), 3, buf_2 };
        const Dark_Array arrv_3 = { sizeof(int32_t), 5, buf_3 };

        const int32_t element = 2;


        DARK_TEST_EQ_P(dark_find_linear_reverse(&element, arrv_1, (Dark_Compare)dark_compare_i32), buf_1 + 4);

        DARK_TEST_EQ_P(dark_find_linear_reverse(&element, arrv_2, (Dark_Compare)dark_compare_i32), buf_2 + 1);

        DARK_TEST_EQ_P(dark_find_linear_reverse(&element, arrv_3, (Dark_Compare)dark_compare_i32), buf_3 + 4);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("find_binary")
    {
        int32_t buf_1[] = {1, 2, 3};
        int32_t buf_2[] = {2, 3, 4, 5, 6};

        const Dark_Array arrv_1 = { sizeof(int32_t), 3, buf_1 };
        const Dark_Array arrv_2 = { sizeof(int32_t), 5, buf_2 };

        const int32_t element = 2;


        DARK_TEST_EQ_P(dark_find_binary(&element, arrv_1, (Dark_Compare)dark_compare_i32), buf_1 + 1);

        DARK_TEST_EQ_P(dark_find_binary(&element, arrv_2, (Dark_Compare)dark_compare_i32), buf_2 + 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("find_view_linear")
    {
        int32_t buf_1[] = {2, 1, 3, 4, 2};
        int32_t buf_2[] = {1, 2, 3};
        int32_t buf_3[] = {1, 1, 3, 4, 2};

        const Dark_Array_View arr_1 = { sizeof(int32_t), 5, buf_1 };
        const Dark_Array_View arr_2 = { sizeof(int32_t), 3, buf_2 };
        const Dark_Array_View arr_3 = { sizeof(int32_t), 5, buf_3 };

        const int32_t element = 2;


        DARK_TEST_EQ_P(dark_find_view_linear(&element, arr_1, (Dark_Compare)dark_compare_i32), buf_1 + 0);

        DARK_TEST_EQ_P(dark_find_view_linear(&element, arr_2, (Dark_Compare)dark_compare_i32), buf_2 + 1);

        DARK_TEST_EQ_P(dark_find_view_linear(&element, arr_3, (Dark_Compare)dark_compare_i32), buf_3 + 4);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("find_view_linear_reverse")
    {
        int32_t buf_1[] = {2, 1, 3, 4, 2};
        int32_t buf_2[] = {1, 2, 3};
        int32_t buf_3[] = {1, 1, 3, 4, 2};

        const Dark_Array_View arr_1 = { sizeof(int32_t), 5, buf_1 };
        const Dark_Array_View arr_2 = { sizeof(int32_t), 3, buf_2 };
        const Dark_Array_View arr_3 = { sizeof(int32_t), 5, buf_3 };

        const int32_t element = 2;


        DARK_TEST_EQ_P(dark_find_view_linear_reverse(&element, arr_1, (Dark_Compare)dark_compare_i32), buf_1 + 4);

        DARK_TEST_EQ_P(dark_find_view_linear_reverse(&element, arr_2, (Dark_Compare)dark_compare_i32), buf_2 + 1);

        DARK_TEST_EQ_P(dark_find_view_linear_reverse(&element, arr_3, (Dark_Compare)dark_compare_i32), buf_3 + 4);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("find_view_binary")
    {
        int32_t buf_1[] = {1, 2, 3};
        int32_t buf_2[] = {2, 3, 4, 5, 6};

        const Dark_Array_View arr_1 = { sizeof(int32_t), 3, buf_1 };
        const Dark_Array_View arr_2 = { sizeof(int32_t), 5, buf_2 };

        const int32_t element = 2;


        DARK_TEST_EQ_P(dark_find_view_binary(&element, arr_1, (Dark_Compare)dark_compare_i32), buf_1 + 1);

        DARK_TEST_EQ_P(dark_find_view_binary(&element, arr_2, (Dark_Compare)dark_compare_i32), buf_2 + 0);
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

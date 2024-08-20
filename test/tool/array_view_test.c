#include <dark/darkstar.h>
#include <dark/darktest.h>

void foreach_helper(int32_t* element, int32_t* constext)
{
    *constext += *element;
}

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("array_view_to")
    {
        int32_t buffer[5] = { 0, 1, 2, 3, 4 };
        Dark_Array_View array_view = { sizeof(int32_t), 5, buffer};

        dark_array_view_to_buffer_view(array_view);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_view_foreach")
    {
        int32_t buffer[5] = { 0, 1, 2, 3, 4 };
        Dark_Array_View array_view = { sizeof(int32_t), 5, buffer};

        int32_t sum = 0;
        dark_array_view_foreach(array_view, &sum, (Dark_Foreach)foreach_helper);

        DARK_TEST_EQ_I(sum, 10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_view_compare")
    {
        int32_t buffer_1[5] = { 0, 1, 2, 3, 4 };
        Dark_Array_View array_view_1 = { sizeof(int32_t), 5, buffer_1};

        int32_t buffer_2[5] = { 0, 1, 2, 3, 4 };
        Dark_Array_View array_view_2 = { sizeof(int32_t), 5, buffer_2};

        int32_t buffer_3[5] = { 0, 1, 2, 99, 4 };
        Dark_Array_View array_view_3 = { sizeof(int32_t), 5, buffer_3};

        DARK_TEST_NE_U(0, dark_array_view_compare(&array_view_1, &array_view_3));
        DARK_TEST_EQ_U(0, dark_array_view_compare(&array_view_1, &array_view_2));
        DARK_TEST_NE_U(0, dark_array_view_compare(&array_view_2, &array_view_3));
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

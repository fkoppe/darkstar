#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("array_to")
    {
        int32_t buffer[5] = { 0, 1, 2, 3, 4 };
        Dark_Array array = { sizeof(int32_t), 5, buffer};

        dark_array_to_view(array);
        dark_array_to_buffer(array);
        dark_array_to_buffer_view(array);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_foreach")
    {
        int32_t buffer[5] = { 0, 1, 2, 3, 4 };
        Dark_Array array = { sizeof(int32_t), 5, buffer};

        int32_t sum = 0;
        dark_array_foreach(array, &sum, (Dark_Foreach)foreach_helper);

        DARK_TEST_EQ_I(sum, 10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_compare")
    {
        int32_t buffer[5] = { 0, 1, 2, 3, 4 };
        Dark_Array array_1 = { sizeof(int32_t), 5, buffer};

        int32_t buffer[5] = { 0, 1, 2, 3, 4 };
        Dark_Array array_2 = { sizeof(int32_t), 5, buffer};

        int32_t buffer[5] = { 0, 1, 2, 99, 4 };
        Dark_Array array_3 = { sizeof(int32_t), 5, buffer};

        DARK_TEST_NE_U(0, dark_array_compare(&array_1, &array_3));
        DARK_TEST_EQ_U(0, dark_array_compare(&array_1, &array_2));
        DARK_TEST_NE_U(0, dark_array_compare(&array_2, &array_3));
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

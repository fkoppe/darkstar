#include <dark/darkstar.h>
#include <dark/darktest.h>

void foreach_helper(uint8_t* element, int32_t* constext)
{
    *constext += 1;
}

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("buffer_to")
    {
        int32_t buf[5] = { 0, 1, 2, 3, 4 };
        Dark_Buffer buffer = { 5 * sizeof(int32_t), buf };

        dark_buffer_to_view(buffer);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("buffer_foreach")
    {
        int32_t buf[5] = { 0, 1, 2, 3, 4 };
        Dark_Buffer buffer = { 5 * sizeof(int32_t), buf };

        int32_t count = 0;
        dark_buffer_foreach(buffer, &count, (Dark_Foreach)foreach_helper);

        DARK_TEST_EQ_I(count, 5 * sizeof(int32_t));
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

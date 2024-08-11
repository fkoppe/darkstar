#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("buffer_to")
    {
        int32_t buf[5] = { 0, 1, 2, 3, 4 };
        Dark_Buffer buffer = { 5, buffer * sizeof(int32_t)};

        dark_buffer_to_view(buffer);
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

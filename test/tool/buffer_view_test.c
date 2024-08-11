#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("buffer_view_to")
    {
        int32_t buf[5] = { 0, 1, 2, 3, 4 };
        Dark_Buffer_View buffer_view = { 5, buf * sizeof(int32_t) };

        dark_array_view_to_buffer_view(buffer_view);
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

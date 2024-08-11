#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("cstring_lenght")
    {
        DARK_TEST_EQ_U(26, dark_cstring_lenght("abcdefghijklmnopqrstuvwxyz"));
        DARK_TEST_EQ_U(0, dark_cstring_lenght(""));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("cstring_to")
    {
        dark_cstring_to_cbuffer_view("hello");
        dark_cstring_to_cbuffer_view_terminated("hello");
        dark_cstring_to_array_view("hello");
        dark_cstring_to_array_view_terminated("hello");
        dark_cstring_to_buffer_view("hello");
        dark_cstring_to_buffer_view_terminated("hello");
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("cstring_compare")
    {
        DARK_TEST_EQ_U(0, dark_cstring_compare("abcd", "abcd"));
        DARK_TEST_NE_U(0, dark_cstring_compare("abcdy", "abcdx"));
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

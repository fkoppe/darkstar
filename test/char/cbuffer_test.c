#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("cbuffer")
    {
        char buf[16] = "merry christmas";

        const Dark_Cbuffer cbuffer = { 16, buf };

        dark_cbuffer_view(cbuffer);
        dark_cbuffer_array(cbuffer);
        dark_cbuffer_array_view(cbuffer);
        dark_cbuffer_view_array_view(dark_cbuffer_view(cbuffer));
        dark_cbuffer_buffer(cbuffer);
        dark_cbuffer_buffer_view(cbuffer);
        dark_cbuffer_view_buffer_view(dark_cbuffer_view(cbuffer));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("cbuffer_terminated_is")
    {
        char buf[16] = "merry christmas";

        const Dark_Cbuffer cbuffer = { 16, buf };

        size_t cstring_lenght = 0;
        DARK_TEST_TRUE(dark_cbuffer_terminated_is(cbuffer, &cstring_lenght));

        DARK_TEST_EQ_U(cstring_lenght, 16 - 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("cbuffer_view_terminated_is")
    {
        char buf[16] = "merry christmas";

        const Dark_Cbuffer cbuffer = { 16, buf };

        size_t cstring_lenght = 0;
        DARK_TEST_TRUE(dark_cbuffer_view_terminated_is(dark_cbuffer_view(cbuffer), &cstring_lenght));

        DARK_TEST_EQ_U(cstring_lenght, 16 - 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("cbuffer_compare/_view_compare")
    {
        char buf_1[16] = "merry christmas";
        const Dark_Cbuffer cbuffer_1 = { 16, buf_1 };

        char buf_2[5] = "abcd";
        const Dark_Cbuffer cbuffer_2 = { 5, buf_2 };

        char buf_3[5] = "abcd";
        const Dark_Cbuffer cbuffer_3 = { 5, buf_3 };

        char buf_4[5] = "abcx";
        const Dark_Cbuffer cbuffer_4 = { 5, buf_4 };

        DARK_TEST_NE_U(0, dark_cbuffer_compare(&cbuffer_1, &cbuffer_2));
        DARK_TEST_EQ_U(0, dark_cbuffer_compare(&cbuffer_2, &cbuffer_3));
        DARK_TEST_NE_U(0, dark_cbuffer_compare(&cbuffer_3, &cbuffer_4));
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

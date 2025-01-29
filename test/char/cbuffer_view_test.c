#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("cbuffer_view_sprintf")
    {
        char buf[16] = "merry christmas";

        const Dark_Cbuffer_View cbuffer_view = { 16, buf };

        char dest[16];
        const Dark_Cbuffer cbuffer = { 16, dest };

        DARK_TEST_EQ_U(dark_snprintf_notterminated(cbuffer.size, cbuffer.data, "%v", cbuffer_view), 16);

        DARK_TEST_EQ_S(buf, dest, 16);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("cbuffer_view_to")
    {
        char buf[16] = "merry christmas";

        const Dark_Cbuffer_View cbuffer_view = { 16, buf };

        dark_cbuffer_view_to_array_view(cbuffer_view);
        dark_cbuffer_view_to_buffer_view(cbuffer_view);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("cbuffer_view_terminated_is")
    {
        char buf[16] = "merry christmas";

        const Dark_Cbuffer_View cbuffer_view = { 16, buf };

        size_t cstring_lenght = 0;
        DARK_TEST_TRUE(dark_cbuffer_view_terminated_is(cbuffer_view, &cstring_lenght));

        DARK_TEST_EQ_U(cstring_lenght, 16 - 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("cbuffer_view_compare")
    {
        char buf_1[16] = "merry christmas";
        const Dark_Cbuffer_View cbuffer_view_1 = { 16, buf_1 };

        char buf_2[5] = "abcd";
        const Dark_Cbuffer_View cbuffer_view_2 = { 5, buf_2 };

        char buf_3[5] = "abcd";
        const Dark_Cbuffer_View cbuffer_view_3 = { 5, buf_3 };

        char buf_4[5] = "abcx";
        const Dark_Cbuffer_View cbuffer_view_4 = { 5, buf_4 };

        DARK_TEST_NE_U(0, dark_cbuffer_view_compare(&cbuffer_view_1, &cbuffer_view_2));
        DARK_TEST_EQ_U(0, dark_cbuffer_view_compare(&cbuffer_view_2, &cbuffer_view_3));
        DARK_TEST_NE_U(0, dark_cbuffer_view_compare(&cbuffer_view_3, &cbuffer_view_4));
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

#include <dark/darkstar.h>

int main()
{
    //----------TEST----------
    DARK_TEST("cstring_lenght")
    {
        DARK_TEST_EQ_U(26, dark_cstring_lenght("abcdefghijklmnopqrstuvwxyz"));
        DARK_TEST_EQ_U(0, dark_cstring_lenght(""));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("cstring_compare")
    {
        DARK_TEST_EQ_U(0, dark_cstring_compare("abcd", "abcd"));
        DARK_TEST_NE_U(0, dark_cstring_compare("abcdy", "abcdx"));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("digit_get_u")
    {
        DARK_TEST_EQ_U(1, dark_digit_get_u(4711, 0));
        DARK_TEST_EQ_U(1, dark_digit_get_u(4711, 1));
        DARK_TEST_EQ_U(7, dark_digit_get_u(4711, 2));
        DARK_TEST_EQ_U(4, dark_digit_get_u(4711, 3));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("digit_get_i")
    {
        DARK_TEST_EQ_U(1, dark_digit_get_i(4711, 0));
        DARK_TEST_EQ_U(1, dark_digit_get_i(4711, 1));
        DARK_TEST_EQ_U(7, dark_digit_get_i(4711, 2));
        DARK_TEST_EQ_U(4, dark_digit_get_i(4711, 3));

        DARK_TEST_EQ_U(2, dark_digit_get_i(-42, 0));
        DARK_TEST_EQ_U(4, dark_digit_get_i(-42, 1));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("digit_to_char")
    {
        DARK_TEST_EQ_U('0', dark_digit_to_char(0));
        DARK_TEST_EQ_U('1', dark_digit_to_char(1));
        DARK_TEST_EQ_U('2', dark_digit_to_char(2));
        DARK_TEST_EQ_U('3', dark_digit_to_char(3));
        DARK_TEST_EQ_U('4', dark_digit_to_char(4));
        DARK_TEST_EQ_U('5', dark_digit_to_char(5));
        DARK_TEST_EQ_U('6', dark_digit_to_char(6));
        DARK_TEST_EQ_U('7', dark_digit_to_char(7));
        DARK_TEST_EQ_U('8', dark_digit_to_char(8));
        DARK_TEST_EQ_U('9', dark_digit_to_char(9));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("digit_count_u8")
    {
        DARK_TEST_EQ_U(3, dark_digit_count_u8(145));
        DARK_TEST_EQ_U(1, dark_digit_count_u8(0));

        DARK_TEST_LE_U(dark_digit_count_i64(UINT8_MAX), DARK_DIGIT_COUNT_MAX_U8);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("digit_count_u16")
    {
        DARK_TEST_EQ_U(3, dark_digit_count_u16(325));
        DARK_TEST_EQ_U(1, dark_digit_count_u16(0));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("digit_count_u32")
    {
        DARK_TEST_EQ_U(5, dark_digit_count_u32(12345));
        DARK_TEST_EQ_U(1, dark_digit_count_u32(0));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("digit_count_u64")
    {
        DARK_TEST_EQ_U(5, dark_digit_count_u64(12345));
        DARK_TEST_EQ_U(1, dark_digit_count_u64(0));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("digit_count_i8")
    {
        DARK_TEST_EQ_U(3, dark_digit_count_i8(122));
        DARK_TEST_EQ_U(2, dark_digit_count_i8(-12));
        DARK_TEST_EQ_U(1, dark_digit_count_i8(1));
        DARK_TEST_EQ_U(1, dark_digit_count_i8(-1));

        DARK_TEST_LE_U(dark_digit_count_i64(INT8_MAX), DARK_DIGIT_COUNT_MAX_I8);
    }
    //--------------------------

    //----------TEST---------
    DARK_TEST("digit_count_i16")
    {
        DARK_TEST_EQ_U(3, dark_digit_count_i16(199));
        DARK_TEST_EQ_U(2, dark_digit_count_i16(-12));
        DARK_TEST_EQ_U(1, dark_digit_count_i16(1));
        DARK_TEST_EQ_U(1, dark_digit_count_i16(-1));
    }
    //--------------------------

    //----------TEST---------
    DARK_TEST("digit_count_i32")
    {
        DARK_TEST_EQ_U(6, dark_digit_count_i32(195659));
        DARK_TEST_EQ_U(2, dark_digit_count_i32(-12));
        DARK_TEST_EQ_U(1, dark_digit_count_i32(1));
        DARK_TEST_EQ_U(1, dark_digit_count_i32(-1));
    }
    //--------------------------

    //----------TEST---------
    DARK_TEST("digit_count_i64")
    {
        DARK_TEST_EQ_U(6, dark_digit_count_i64(196669));
        DARK_TEST_EQ_U(2, dark_digit_count_i64(-12));
        DARK_TEST_EQ_U(1, dark_digit_count_i64(1));
        DARK_TEST_EQ_U(1, dark_digit_count_i64(-1));
    }
    //--------------------------

    //----------TEST---------
    DARK_TEST("digit_to_cbuffer_u")
    {
        const char* const cstring = "1234";
        char cbuffer[DARK_DIGIT_COUNT_MAX_U64]= "aaaaaaaaaaaaaaaaaaaa"; //20
        size_t lenght = 0;

        dark_digit_to_cbuffer_u(55435, 5, cbuffer);

        DARK_TEST_FALSE(dark_cbuffer_terminated_is(DARK_DIGIT_COUNT_MAX_I64, cbuffer, &lenght));
    }
    //--------------------------

    //----------TEST---------
    DARK_TEST("digit_to_cbuffer_u_terminated")
    {
        const char* const cstring = "1234";
        char cbuffer[DARK_DIGIT_COUNT_MAX_U64] = "aaaaaaaaaaaaaaaaaaaa"; //20
        size_t lenght = 0;

        dark_digit_to_cbuffer_u_terminated(955435, 6, cbuffer);

        DARK_TEST_TRUE(dark_cbuffer_terminated_is(DARK_DIGIT_COUNT_MAX_I64, cbuffer, &lenght));
        DARK_TEST_EQ_U(6, lenght);
    }
    //--------------------------

    //----------TEST---------
    DARK_TEST("digit_to_cbuffer_i")
    {
        const char* const cstring = "1234";
        char cbuffer[DARK_DIGIT_COUNT_MAX_I64] = "aaaaaaaaaaaaaaaaaaa"; //19
        size_t lenght = 0;

        dark_digit_to_cbuffer_i(-9555, 4, cbuffer);

        DARK_TEST_FALSE(dark_cbuffer_terminated_is(DARK_DIGIT_COUNT_MAX_I64, cbuffer, &lenght));
    }
    //--------------------------

    //----------TEST---------
    DARK_TEST("digit_to_cbuffer_i_terminated")
    {
        const char* const cstring = "1234";
        char cbuffer[DARK_DIGIT_COUNT_MAX_I64] = "aaaaaaaaaaaaaaaaaaa"; //19
        size_t lenght = 0;

        dark_digit_to_cbuffer_i_terminated(955435, 6, cbuffer);

        DARK_TEST_TRUE(dark_cbuffer_terminated_is(DARK_DIGIT_COUNT_MAX_I64, cbuffer, &lenght));
        DARK_TEST_EQ_U(6, lenght);
    }
    //--------------------------

    dark_test_end();

    return EXIT_SUCCESS;
}

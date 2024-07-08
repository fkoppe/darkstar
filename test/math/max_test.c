#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("max_u8")
    {
        DARK_TEST_EQ_U(dark_max_u8(0, 0), 0);
        DARK_TEST_EQ_U(dark_max_u8(UINT8_MAX, 0), UINT8_MAX);
        DARK_TEST_EQ_U(dark_max_u8(0, UINT8_MAX), UINT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("max_u16")
    {
        DARK_TEST_EQ_U(dark_max_u16(0, 0), 0);
        DARK_TEST_EQ_U(dark_max_u16(UINT16_MAX, 0), UINT16_MAX);
        DARK_TEST_EQ_U(dark_max_u16(0, UINT16_MAX), UINT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("max_u32")
    {
        DARK_TEST_EQ_U(dark_max_u32(0, 0), 0);
        DARK_TEST_EQ_U(dark_max_u32(UINT32_MAX, 0), UINT32_MAX);
        DARK_TEST_EQ_U(dark_max_u32(0, UINT32_MAX), UINT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("max_u64")
    {
        DARK_TEST_EQ_U(dark_max_u64(0, 0), 0);
        DARK_TEST_EQ_U(dark_max_u64(UINT64_MAX, 0), UINT64_MAX);
        DARK_TEST_EQ_U(dark_max_u64(0, UINT64_MAX), UINT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("max_umax")
    {
        DARK_TEST_EQ_U(dark_max_umax(0, 0), 0);
        DARK_TEST_EQ_U(dark_max_umax(UINTMAX_MAX, 0), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_max_umax(0, UINTMAX_MAX), UINTMAX_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("max_zu")
    {
        DARK_TEST_EQ_U(dark_max_zu(0, 0), 0);
        DARK_TEST_EQ_U(dark_max_zu(SIZE_MAX, 0), SIZE_MAX);
        DARK_TEST_EQ_U(dark_max_zu(0, SIZE_MAX), SIZE_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("max_i8")
    {
        DARK_TEST_EQ_I(dark_max_i8(0, 0), 0);
        DARK_TEST_EQ_I(dark_max_i8(INT8_MAX, INT8_MIN), INT8_MAX);
        DARK_TEST_EQ_I(dark_max_i8(INT8_MIN, INT8_MAX), INT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("max_i16")
    {
        DARK_TEST_EQ_I(dark_max_i16(0, 0), 0);
        DARK_TEST_EQ_I(dark_max_i16(INT16_MAX, INT16_MIN), INT16_MAX);
        DARK_TEST_EQ_I(dark_max_i16(INT16_MIN, INT16_MAX), INT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("max_i32")
    {
        DARK_TEST_EQ_I(dark_max_i32(0, 0), 0);
        DARK_TEST_EQ_I(dark_max_i32(INT32_MAX, INT32_MIN), INT32_MAX);
        DARK_TEST_EQ_I(dark_max_i32(INT32_MIN, INT32_MAX), INT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("max_i64")
    {
        DARK_TEST_EQ_I(dark_max_i64(0, 0), 0);
        DARK_TEST_EQ_I(dark_max_i64(INT64_MAX, INT64_MIN), INT64_MAX);
        DARK_TEST_EQ_I(dark_max_i64(INT64_MIN, INT64_MAX), INT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("max_i64")
    {
        DARK_TEST_EQ_I(dark_max_i64(0, 0), 0);
        DARK_TEST_EQ_I(dark_max_i64(INT64_MAX, INT64_MIN), INT64_MAX);
        DARK_TEST_EQ_I(dark_max_i64(INT64_MIN, INT64_MAX), INT64_MAX);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

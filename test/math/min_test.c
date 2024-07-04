#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("min_u8")
    {
        DARK_TEST_EQ_U(dark_min_u8(0, 0), 0);
        DARK_TEST_EQ_U(dark_min_u8(UINT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_min_u8(0, UINT8_MAX), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("min_u16")
    {
        DARK_TEST_EQ_U(dark_min_u16(0, 0), 0);
        DARK_TEST_EQ_U(dark_min_u16(UINT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_min_u16(0, UINT16_MAX), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("min_u32")
    {
        DARK_TEST_EQ_U(dark_min_u32(0, 0), 0);
        DARK_TEST_EQ_U(dark_min_u32(UINT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_min_u32(0, UINT32_MAX), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("min_u64")
    {
        DARK_TEST_EQ_U(dark_min_u64(0, 0), 0);
        DARK_TEST_EQ_U(dark_min_u64(UINT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_min_u64(0, UINT64_MAX), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("min_umin")
    {
        DARK_TEST_EQ_U(dark_min_umax(0, 0), 0);
        DARK_TEST_EQ_U(dark_min_umax(UINTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_min_umax(0, UINTMAX_MAX), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("min_zu")
    {
        DARK_TEST_EQ_U(dark_min_zu(0, 0), 0);
        DARK_TEST_EQ_U(dark_min_zu(SIZE_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_min_zu(0, SIZE_MAX), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("min_i8")
    {
        DARK_TEST_EQ_I(dark_min_i8(0, 0), 0);
        DARK_TEST_EQ_I(dark_min_i8(INT8_MAX, INT8_MIN), INT8_MIN);
        DARK_TEST_EQ_I(dark_min_i8(INT8_MIN, INT8_MAX), INT8_MIN);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("min_i16")
    {
        DARK_TEST_EQ_I(dark_min_i16(0, 0), 0);
        DARK_TEST_EQ_I(dark_min_i16(INT16_MAX, INT16_MIN), INT16_MIN);
        DARK_TEST_EQ_I(dark_min_i16(INT16_MIN, INT16_MAX), INT16_MIN);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("min_i32")
    {
        DARK_TEST_EQ_I(dark_min_i32(0, 0), 0);
        DARK_TEST_EQ_I(dark_min_i32(INT32_MAX, INT32_MIN), INT32_MIN);
        DARK_TEST_EQ_I(dark_min_i32(INT32_MIN, INT32_MAX), INT32_MIN);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("min_i64")
    {
        DARK_TEST_EQ_I(dark_min_i64(0, 0), 0);
        DARK_TEST_EQ_I(dark_min_i64(INT64_MAX, INT64_MIN), INT64_MIN);
        DARK_TEST_EQ_I(dark_min_i64(INT64_MIN, INT64_MAX), INT64_MIN);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("min_i64")
    {
        DARK_TEST_EQ_I(dark_min_i64(0, 0), 0);
        DARK_TEST_EQ_I(dark_min_i64(INT64_MAX, INT64_MIN), INT64_MIN);
        DARK_TEST_EQ_I(dark_min_i64(INT64_MIN, INT64_MAX), INT64_MIN);
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

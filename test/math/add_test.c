#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("add_u8")
    {
        DARK_TEST_EQ_U(dark_add_u8(0, 0), 0);
        DARK_TEST_EQ_U(dark_add_u8(UINT8_MAX - 1, 1), UINT8_MAX);
        DARK_TEST_EQ_U(dark_add_u8(255, -30), 225);
        DARK_TEST_EQ_U(dark_add_u8(UINT8_MAX, -UINT8_MAX), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("add_u16")
    {
        DARK_TEST_EQ_U(dark_add_u16(0, 0), 0);
        DARK_TEST_EQ_U(dark_add_u16(UINT16_MAX - 1, 1), UINT16_MAX);
        DARK_TEST_EQ_U(dark_add_u16(255, -30), 225);
        DARK_TEST_EQ_U(dark_add_u16(UINT16_MAX, -UINT16_MAX), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("add_u32")
    {
        DARK_TEST_EQ_U(dark_add_u32(0, 0), 0);
        DARK_TEST_EQ_U(dark_add_u32(UINT32_MAX - 1, 1), UINT32_MAX);
        DARK_TEST_EQ_U(dark_add_u32(255, -30), 225);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("add_u64")
    {
        DARK_TEST_EQ_U(dark_add_u64(0, 0), 0);
        DARK_TEST_EQ_U(dark_add_u64(UINT64_MAX - 1, 1), UINT64_MAX);
        DARK_TEST_EQ_U(dark_add_u64(255, -30), 225);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("add_umax")
    {
        DARK_TEST_EQ_U(dark_add_umax(0, 0), 0);
        DARK_TEST_EQ_U(dark_add_umax(UINTMAX_MAX - 1, 1), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_add_umax(255, -30), 225);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("add_zu")
    {
        DARK_TEST_EQ_U(dark_add_zu(0, 0), 0);
        DARK_TEST_EQ_U(dark_add_zu(SIZE_MAX - 1, 1), SIZE_MAX);
        DARK_TEST_EQ_U(dark_add_zu(255, -30), 225);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_u8")
    {
        DARK_TEST_EQ_U(dark_uadd_u8(0, 0), 0);
        DARK_TEST_EQ_U(dark_uadd_u8(UINT8_MAX - 1, 1), UINT8_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_u16")
    {
        DARK_TEST_EQ_U(dark_uadd_u16(0, 0), 0);
        DARK_TEST_EQ_U(dark_uadd_u16(UINT16_MAX - 1, 1), UINT16_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_u32")
    {
        DARK_TEST_EQ_U(dark_uadd_u32(0, 0), 0);
        DARK_TEST_EQ_U(dark_uadd_u32(UINT32_MAX - 1, 1), UINT32_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_u64")
    {
        DARK_TEST_EQ_U(dark_uadd_u64(0, 0), 0);
        DARK_TEST_EQ_U(dark_uadd_u64(UINT64_MAX - 1, 1), UINT64_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_umax")
    {
        DARK_TEST_EQ_U(dark_uadd_umax(0, 0), 0);
        DARK_TEST_EQ_U(dark_uadd_umax(UINTMAX_MAX - 1, 1), UINTMAX_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_zu")
    {
        DARK_TEST_EQ_U(dark_uadd_zu(0, 0), 0);
        DARK_TEST_EQ_U(dark_uadd_zu(SIZE_MAX - 1, 1), SIZE_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_u8")
    {
        DARK_TEST_EQ_U(dark_iadd_u8(0, 0), 0);
        DARK_TEST_EQ_U(dark_iadd_u8(-200, 201), 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_u16")
    {
        DARK_TEST_EQ_U(dark_iadd_u16(0, 0), 0);
        DARK_TEST_EQ_U(dark_iadd_u16(-200, 201), 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_u32")
    {
        DARK_TEST_EQ_U(dark_iadd_u32(0, 0), 0);
        DARK_TEST_EQ_U(dark_iadd_u32(-200, 201), 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_u64")
    {
        DARK_TEST_EQ_U(dark_iadd_u64(0, 0), 0);
        DARK_TEST_EQ_U(dark_iadd_u64(-200, 201), 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_umax")
    {
        DARK_TEST_EQ_U(dark_iadd_umax(0, 0), 0);
        DARK_TEST_EQ_U(dark_iadd_umax(-200, 201), 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_zu")
    {
        DARK_TEST_EQ_U(dark_iadd_zu(0, 0), 0);
        DARK_TEST_EQ_U(dark_iadd_zu(-200, 201), 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("add_i8")
    {
        DARK_TEST_EQ_I(dark_add_i8(0, 0), 0);
        DARK_TEST_EQ_I(dark_add_i8(INT8_MAX - 1, 1), INT8_MAX);
        DARK_TEST_EQ_I(dark_add_i8(INT8_MAX, -30), INT8_MAX - 30);
        DARK_TEST_EQ_I(dark_add_i8(INT8_MAX, -INT8_MAX), 0);

        DARK_TEST_EQ_I(dark_add_i8(50, -60), -10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("add_i16")
    {
        DARK_TEST_EQ_I(dark_add_i16(0, 0), 0);
        DARK_TEST_EQ_I(dark_add_i16(INT16_MAX - 1, 1), INT16_MAX);
        DARK_TEST_EQ_I(dark_add_i16(255, -30), 225);
        DARK_TEST_EQ_I(dark_add_i16(INT16_MAX, -INT16_MAX), 0);

        DARK_TEST_EQ_I(dark_add_i16(50, -60), -10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("add_i32")
    {
        DARK_TEST_EQ_I(dark_add_i32(0, 0), 0);
        DARK_TEST_EQ_I(dark_add_i32(INT32_MAX - 1, 1), INT32_MAX);
        DARK_TEST_EQ_I(dark_add_i32(255, -30), 225);

        DARK_TEST_EQ_I(dark_add_i32(50, -60), -10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("add_i64")
    {
        DARK_TEST_EQ_I(dark_add_i64(0, 0), 0);
        DARK_TEST_EQ_I(dark_add_i64(INT64_MAX - 1, 1), INT64_MAX);
        DARK_TEST_EQ_I(dark_add_i64(255, -30), 225);

        DARK_TEST_EQ_I(dark_add_i64(50, -60), -10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("add_imax")
    {
        DARK_TEST_EQ_I(dark_add_imax(0, 0), 0);
        DARK_TEST_EQ_I(dark_add_imax(INTMAX_MAX - 1, 1), INTMAX_MAX);
        DARK_TEST_EQ_I(dark_add_imax(255, -30), 225);

        DARK_TEST_EQ_I(dark_add_imax(50, -60), -10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_i8")
    {
        DARK_TEST_EQ_I(dark_uadd_i8(0, 0), 0);
        DARK_TEST_EQ_I(dark_uadd_i8(INT8_MAX - 1, 1), INT8_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_i16")
    {
        DARK_TEST_EQ_I(dark_uadd_i16(0, 0), 0);
        DARK_TEST_EQ_I(dark_uadd_i16(INT16_MAX - 1, 1), INT16_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_i32")
    {
        DARK_TEST_EQ_I(dark_uadd_i32(0, 0), 0);
        DARK_TEST_EQ_I(dark_uadd_i32(INT32_MAX - 1, 1), INT32_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_i64")
    {
        DARK_TEST_EQ_I(dark_uadd_i64(0, 0), 0);
        DARK_TEST_EQ_I(dark_uadd_i64(INT64_MAX - 1, 1), INT64_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("uadd_imax")
    {
        DARK_TEST_EQ_I(dark_uadd_imax(0, 0), 0);
        DARK_TEST_EQ_I(dark_uadd_imax(INTMAX_MAX - 1, 1), INTMAX_MAX);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_i8")
    {
        DARK_TEST_EQ_I(dark_iadd_i8(0, 0), 0);
        DARK_TEST_EQ_I(dark_iadd_i8(-200, 201), 1);

        DARK_TEST_EQ_I(dark_iadd_i8(-50, -50), -100);
        DARK_TEST_EQ_I(dark_iadd_i8(50, -60), -10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_i16")
    {
        DARK_TEST_EQ_I(dark_iadd_i16(0, 0), 0);
        DARK_TEST_EQ_I(dark_iadd_i16(-200, 201), 1);

        DARK_TEST_EQ_I(dark_iadd_i32(-50, -50), -100);
        DARK_TEST_EQ_I(dark_iadd_i32(50, -60), -10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_i32")
    {
        DARK_TEST_EQ_I(dark_iadd_i32(0, 0), 0);
        DARK_TEST_EQ_I(dark_iadd_i32(-200, 201), 1);

        DARK_TEST_EQ_I(dark_iadd_i32(-50, -50), -100);
        DARK_TEST_EQ_I(dark_iadd_i32(50, -60), -10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_i64")
    {
        DARK_TEST_EQ_I(dark_iadd_i64(0, 0), 0);
        DARK_TEST_EQ_I(dark_iadd_i64(-200, 201), 1);

        DARK_TEST_EQ_I(dark_iadd_i64(-50, -50), -100);
        DARK_TEST_EQ_I(dark_iadd_i64(50, -60), -10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iadd_imax")
    {
        DARK_TEST_EQ_I(dark_iadd_imax(0, 0), 0);
        DARK_TEST_EQ_I(dark_iadd_imax(-200, 201), 1);

        DARK_TEST_EQ_I(dark_iadd_imax(-50, -50), -100);
        DARK_TEST_EQ_I(dark_iadd_imax(50, -60), -10);
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("mult_u8")
    {
        DARK_TEST_EQ_U(dark_mult_u8(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_u8(UINT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_u8(0, UINT8_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_u8(UINT8_MAX, 1), UINT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("mult_u16")
    {
        DARK_TEST_EQ_U(dark_mult_u16(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_u16(UINT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_u16(0, UINT16_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_u16(UINT16_MAX, 1), UINT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("mult_u32")
    {
        DARK_TEST_EQ_U(dark_mult_u32(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_u32(UINT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_u32(0, UINT32_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_u32(UINT32_MAX, 1), UINT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("mult_u64")
    {
        DARK_TEST_EQ_U(dark_mult_u64(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_u64(UINT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_u64(0, UINT64_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_u64(UINT64_MAX, 1), UINT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("mult_umax")
    {
        DARK_TEST_EQ_U(dark_mult_umax(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_umax(UINTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_umax(0, UINTMAX_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_umax(UINTMAX_MAX, 1), UINTMAX_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("mult_zu")
    {
        DARK_TEST_EQ_U(dark_mult_zu(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_zu(SIZE_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_zu(0, SIZE_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_zu(SIZE_MAX, 1), SIZE_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_u8")
    {
        DARK_TEST_EQ_U(dark_umult_u8(1, 1), 1);
        DARK_TEST_EQ_U(dark_umult_u8(UINT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_u8(0, UINT8_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_u8(UINT8_MAX, 1), UINT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_u16")
    {
        DARK_TEST_EQ_U(dark_umult_u16(1, 1), 1);
        DARK_TEST_EQ_U(dark_umult_u16(UINT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_u16(0, UINT16_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_u16(UINT16_MAX, 1), UINT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_u32")
    {
        DARK_TEST_EQ_U(dark_umult_u32(1, 1), 1);
        DARK_TEST_EQ_U(dark_umult_u32(UINT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_u32(0, UINT32_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_u32(UINT32_MAX, 1), UINT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_u64")
    {
        DARK_TEST_EQ_U(dark_umult_u64(1, 1), 1);
        DARK_TEST_EQ_U(dark_umult_u64(UINT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_u64(0, UINT64_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_u64(UINT64_MAX, 1), UINT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_umax")
    {
        DARK_TEST_EQ_U(dark_umult_umax(1, 1), 1);
        DARK_TEST_EQ_U(dark_umult_umax(UINTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_umax(0, UINTMAX_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_umax(UINTMAX_MAX, 1), UINTMAX_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_zu")
    {
        DARK_TEST_EQ_U(dark_umult_zu(1, 1), 1);
        DARK_TEST_EQ_U(dark_umult_zu(SIZE_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_zu(0, SIZE_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_zu(SIZE_MAX, 1), SIZE_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_u8")
    {
        DARK_TEST_EQ_U(dark_imult_u8(-1, -1), 1);
        DARK_TEST_EQ_U(dark_imult_u8(INT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_u8(0, INT8_MAX), 0);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_u16")
    {
        DARK_TEST_EQ_U(dark_imult_u16(-1, -1), 1);
        DARK_TEST_EQ_U(dark_imult_u16(INT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_u16(0, INT16_MAX), 0);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_u32")
    {
        DARK_TEST_EQ_U(dark_imult_u32(-1, -1), 1);
        DARK_TEST_EQ_U(dark_imult_u32(INT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_u32(0, INT32_MAX), 0);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_u64")
    {
        DARK_TEST_EQ_U(dark_imult_u64(-1, -1), 1);
        DARK_TEST_EQ_U(dark_imult_u64(INT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_u64(0, INT64_MAX), 0);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_umax")
    {
        DARK_TEST_EQ_U(dark_imult_umax(-1, -1), 1);
        DARK_TEST_EQ_U(dark_imult_umax(INTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_umax(0, INTMAX_MAX), 0);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_zu")
    {
        DARK_TEST_EQ_U(dark_imult_zu(-1, -1), 1);
        DARK_TEST_EQ_U(dark_imult_zu(INT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_zu(0, INT64_MAX), 0);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("mult_i8")
    {
        DARK_TEST_EQ_U(dark_mult_i8(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_i8(INT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_i8(0, INT8_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_i8(INT8_MAX, 1), INT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("mult_i16")
    {
        DARK_TEST_EQ_U(dark_mult_i16(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_i16(INT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_i16(0, INT16_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_i16(INT16_MAX, 1), INT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("mult_i32")
    {
        DARK_TEST_EQ_U(dark_mult_i32(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_i32(INT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_i32(0, INT32_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_i32(INT32_MAX, 1), INT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("mult_i64")
    {
        DARK_TEST_EQ_U(dark_mult_i64(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_i64(INT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_i64(0, INT64_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_i64(INT64_MAX, 1), INT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("mult_imax")
    {
        DARK_TEST_EQ_U(dark_mult_imax(0, -1), 0);
        DARK_TEST_EQ_U(dark_mult_imax(INTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_imax(0, INTMAX_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_imax(INTMAX_MAX, 1), INTMAX_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_i8")
    {
        DARK_TEST_EQ_U(dark_umult_i8(0, 0), 0);
        DARK_TEST_EQ_U(dark_umult_i8(INT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_i8(0, INT8_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_i8(INT8_MAX, 1), INT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_i16")
    {
        DARK_TEST_EQ_U(dark_umult_i16(0, 0), 0);
        DARK_TEST_EQ_U(dark_umult_i16(INT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_i16(0, INT16_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_i16(INT16_MAX, 1), INT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_i32")
    {
        DARK_TEST_EQ_U(dark_umult_i32(0, 0), 0);
        DARK_TEST_EQ_U(dark_umult_i32(INT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_i32(0, INT32_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_i32(INT32_MAX, 1), INT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_i64")
    {
        DARK_TEST_EQ_U(dark_umult_i64(0, 0), 0);
        DARK_TEST_EQ_U(dark_umult_i64(INT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_i64(0, INT64_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_i64(INT64_MAX, 1), INT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("umult_imax")
    {
        DARK_TEST_EQ_U(dark_umult_imax(0, 0), 0);
        DARK_TEST_EQ_U(dark_umult_imax(INTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_umult_imax(0, INTMAX_MAX), 0);

        DARK_TEST_EQ_U(dark_umult_imax(INTMAX_MAX, 1), INTMAX_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_i8")
    {
        DARK_TEST_EQ_U(dark_imult_i8(0, 0), 0);
        DARK_TEST_EQ_U(dark_imult_i8(INT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_i8(0, INT8_MAX), 0);

        DARK_TEST_EQ_U(dark_imult_i8(INT8_MAX, 1), INT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_i16")
    {
        DARK_TEST_EQ_U(dark_imult_i16(0, 0), 0);
        DARK_TEST_EQ_U(dark_imult_i16(INT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_i16(0, INT16_MAX), 0);

        DARK_TEST_EQ_U(dark_imult_i16(INT16_MAX, 1), INT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_i32")
    {
        DARK_TEST_EQ_U(dark_imult_i32(0, 0), 0);
        DARK_TEST_EQ_U(dark_imult_i32(INT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_i32(0, INT32_MAX), 0);

        DARK_TEST_EQ_U(dark_imult_i32(INT32_MAX, 1), INT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_i64")
    {
        DARK_TEST_EQ_U(dark_imult_i64(0, 0), 0);
        DARK_TEST_EQ_U(dark_imult_i64(INT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_i64(0, INT64_MAX), 0);

        DARK_TEST_EQ_U(dark_imult_i64(INT64_MAX, 1), INT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("imult_imax")
    {
        DARK_TEST_EQ_U(dark_imult_imax(0, 0), 0);
        DARK_TEST_EQ_U(dark_imult_imax(INTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_imult_imax(0, INTMAX_MAX), 0);

        DARK_TEST_EQ_U(dark_imult_imax(INTMAX_MAX, 1), INTMAX_MAX);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("sat_mult_u8")
    {
        DARK_TEST_EQ_U(dark_sat_mult_u8(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u8(UINT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u8(0, UINT8_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u8(UINT8_MAX, 1), UINT8_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_u8(UINT8_MAX, 2), UINT8_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_u8(2, UINT8_MAX), UINT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_mult_u16")
    {
        DARK_TEST_EQ_U(dark_sat_mult_u16(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u16(UINT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u16(0, UINT16_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u16(UINT16_MAX, 1), UINT16_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_u16(UINT16_MAX, 2), UINT16_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_u16(2, UINT16_MAX), UINT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_mult_u32")
    {
        DARK_TEST_EQ_U(dark_sat_mult_u32(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u32(UINT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u32(0, UINT32_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u32(UINT32_MAX, 1), UINT32_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_u32(UINT32_MAX, 2), UINT32_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_u32(2, UINT32_MAX), UINT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_mult_u64")
    {
        DARK_TEST_EQ_U(dark_sat_mult_u64(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u64(UINT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u64(0, UINT64_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_u64(UINT64_MAX, 1), UINT64_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_u64(UINT64_MAX, 2), UINT64_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_u64(2, UINT64_MAX), UINT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_mult_umax")
    {
        DARK_TEST_EQ_U(dark_sat_mult_umax(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_umax(UINTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_umax(0, UINTMAX_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_umax(UINTMAX_MAX, 1), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_umax(UINTMAX_MAX, 2), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_umax(2, UINTMAX_MAX), UINTMAX_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_mult_zu")
    {
        DARK_TEST_EQ_U(dark_sat_mult_zu(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_zu(SIZE_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_zu(0, SIZE_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_zu(SIZE_MAX, 1), SIZE_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_zu(SIZE_MAX, 2), SIZE_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_zu(2, SIZE_MAX), SIZE_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_u8")
    {
        DARK_TEST_EQ_U(dark_sat_umult_u8(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u8(UINT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u8(0, UINT8_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u8(UINT8_MAX, 1), UINT8_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_u8(UINT8_MAX, 2), UINT8_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_u8(2, UINT8_MAX), UINT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_u16")
    {
        DARK_TEST_EQ_U(dark_sat_umult_u16(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u16(UINT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u16(0, UINT16_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u16(UINT16_MAX, 1), UINT16_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_u16(UINT16_MAX, 2), UINT16_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_u16(2, UINT16_MAX), UINT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_u32")
    {
        DARK_TEST_EQ_U(dark_sat_umult_u32(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u32(UINT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u32(0, UINT32_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u32(UINT32_MAX, 1), UINT32_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_u32(UINT32_MAX, 2), UINT32_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_u32(2, UINT32_MAX), UINT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_u64")
    {
        DARK_TEST_EQ_U(dark_sat_umult_u64(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u64(UINT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u64(0, UINT64_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_u64(UINT64_MAX, 1), UINT64_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_u64(UINT64_MAX, 2), UINT64_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_u64(2, UINT64_MAX), UINT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_umax")
    {
        DARK_TEST_EQ_U(dark_sat_umult_umax(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_umax(UINTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_umax(0, UINTMAX_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_umax(UINTMAX_MAX, 1), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_umax(UINTMAX_MAX, 2), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_umax(2, UINTMAX_MAX), UINTMAX_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_zu")
    {
        DARK_TEST_EQ_U(dark_sat_umult_zu(0, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_zu(SIZE_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_zu(0, SIZE_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_zu(SIZE_MAX, 1), SIZE_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_zu(SIZE_MAX, 2), SIZE_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_zu(2, SIZE_MAX), SIZE_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_u8")
    {
        DARK_TEST_EQ_U(dark_sat_imult_u8(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_u8(INT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_u8(0, INT8_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_u8(INT8_MAX, 10), UINT8_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_u8(10, INT8_MAX), UINT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_u16")
    {
        DARK_TEST_EQ_U(dark_sat_imult_u16(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_u16(INT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_u16(0, INT16_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_u16(INT16_MAX, 10), UINT16_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_u16(10, INT16_MAX), UINT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_u32")
    {
        DARK_TEST_EQ_U(dark_sat_imult_u32(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_u32(INT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_u32(0, INT32_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_u32(INT32_MAX, 10), UINT32_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_u32(10, INT32_MAX), UINT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_u64")
    {
        DARK_TEST_EQ_U(dark_sat_imult_u64(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_u64(INT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_u64(0, INT64_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_u64(INT64_MAX, 10), UINT64_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_u64(10, INT64_MAX), UINT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_umax")
    {
        DARK_TEST_EQ_U(dark_sat_imult_umax(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_umax(INTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_umax(0, INTMAX_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_umax(INTMAX_MAX, 10), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_umax(10, INTMAX_MAX), UINTMAX_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_zu")
    {
        DARK_TEST_EQ_U(dark_sat_imult_zu(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_zu(INT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_zu(0, INT64_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_zu(INT64_MAX, 10), SIZE_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_zu(10, INT64_MAX), SIZE_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_mult_i8")
    {
        DARK_TEST_EQ_I(dark_sat_mult_i8(1, -1), -1);
        DARK_TEST_EQ_U(dark_sat_mult_i8(INT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_i8(0, INT8_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_i8(INT8_MAX, 1), INT8_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_i8(INT8_MAX, 2), INT8_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_i8(2, INT8_MAX), INT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_mult_i16")
    {
        DARK_TEST_EQ_I(dark_sat_mult_i16(1, -1), -1);
        DARK_TEST_EQ_U(dark_sat_mult_i16(INT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_i16(0, INT16_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_i16(INT16_MAX, 1), INT16_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_i16(INT16_MAX, 2), INT16_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_i16(2, INT16_MAX), INT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_mult_i32")
    {
        DARK_TEST_EQ_I(dark_sat_mult_i32(1, -1), -1);
        DARK_TEST_EQ_U(dark_sat_mult_i32(INT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_i32(0, INT32_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_i32(INT32_MAX, 1), INT32_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_i32(INT32_MAX, 2), INT32_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_i32(2, INT32_MAX), INT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_mult_i64")
    {
        DARK_TEST_EQ_I(dark_sat_mult_i64(1, -1), -1);
        DARK_TEST_EQ_U(dark_sat_mult_i64(INT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_i64(0, INT64_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_i64(INT64_MAX, 1), INT64_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_i64(INT64_MAX, 2), INT64_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_i64(2, INT64_MAX), INT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_mult_imax")
    {
        DARK_TEST_EQ_I(dark_sat_mult_umax(1, -1), -1);
        DARK_TEST_EQ_U(dark_sat_mult_umax(UINTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_mult_umax(0, UINTMAX_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_mult_umax(UINTMAX_MAX, 1), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_umax(UINTMAX_MAX, 2), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_mult_umax(2, UINTMAX_MAX), UINTMAX_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_i8")
    {
        DARK_TEST_EQ_U(dark_sat_umult_i8(1, 1), 1);
        DARK_TEST_EQ_U(dark_sat_umult_i8(INT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_i8(0, INT8_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_i8(INT8_MAX, 1), INT8_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_i8(INT8_MAX, 2), INT8_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_i8(2, INT8_MAX), INT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_i16")
    {
        DARK_TEST_EQ_U(dark_sat_umult_i16(1, 1), 1);
        DARK_TEST_EQ_U(dark_sat_umult_i16(INT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_i16(0, INT16_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_i16(INT16_MAX, 1), INT16_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_i16(INT16_MAX, 2), INT16_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_i16(2, INT16_MAX), INT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_i32")
    {
        DARK_TEST_EQ_U(dark_sat_umult_i32(1, 1), 1);
        DARK_TEST_EQ_U(dark_sat_umult_i32(INT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_i32(0, INT32_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_i32(INT32_MAX, 1), INT32_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_i32(INT32_MAX, 2), INT32_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_i32(2, INT32_MAX), INT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_i64")
    {
        DARK_TEST_EQ_U(dark_sat_umult_i64(1, 1), 1);
        DARK_TEST_EQ_U(dark_sat_umult_i64(INT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_i64(0, INT64_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_i64(INT64_MAX, 1), INT64_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_i64(INT64_MAX, 2), INT64_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_i64(2, INT64_MAX), INT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_umult_imax")
    {
        DARK_TEST_EQ_U(dark_sat_umult_umax(1, 1), 1);
        DARK_TEST_EQ_U(dark_sat_umult_umax(UINTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_umult_umax(0, UINTMAX_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_umult_umax(UINTMAX_MAX, 1), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_umax(UINTMAX_MAX, 2), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_umult_umax(2, UINTMAX_MAX), UINTMAX_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_i8")
    {
        DARK_TEST_EQ_U(dark_sat_imult_i8(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_i8(INT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_i8(0, INT8_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_i8(INT8_MAX, 1), INT8_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_i8(INT8_MAX, 2), INT8_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_i8(2, INT8_MAX), INT8_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_i16")
    {
        DARK_TEST_EQ_U(dark_sat_imult_i16(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_i16(INT16_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_i16(0, INT16_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_i16(INT16_MAX, 1), INT16_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_i16(INT16_MAX, 2), INT16_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_i16(2, INT16_MAX), INT16_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_i32")
    {
        DARK_TEST_EQ_U(dark_sat_imult_i32(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_i32(INT32_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_i32(0, INT32_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_i32(INT32_MAX, 1), INT32_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_i32(INT32_MAX, 2), INT32_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_i32(2, INT32_MAX), INT32_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_i64")
    {
        DARK_TEST_EQ_U(dark_sat_imult_i64(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_i64(INT64_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_i64(0, INT64_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_i64(INT64_MAX, 1), INT64_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_i64(INT64_MAX, 2), INT64_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_i64(2, INT64_MAX), INT64_MAX);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_imult_imax")
    {
        DARK_TEST_EQ_U(dark_sat_imult_umax(-1, -1), 1);
        DARK_TEST_EQ_U(dark_sat_imult_umax(INTMAX_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_sat_imult_umax(0, INTMAX_MAX), 0);
        DARK_TEST_EQ_U(dark_sat_imult_umax(INTMAX_MAX, 1), INTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_umax(INTMAX_MAX, 10), UINTMAX_MAX);
        DARK_TEST_EQ_U(dark_sat_imult_umax(10, INTMAX_MAX), UINTMAX_MAX);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

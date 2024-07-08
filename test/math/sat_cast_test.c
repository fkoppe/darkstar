#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("sat_ucast_u8/_u16/_u32/_u64")
    {
        DARK_TEST_EQ_U(dark_sat_ucast_u8((uint64_t)UINT8_MAX + 1), UINT8_MAX);
        DARK_TEST_EQ_U(dark_sat_ucast_u16((uint64_t)UINT16_MAX + 1), UINT16_MAX);
        DARK_TEST_EQ_U(dark_sat_ucast_u32((uint64_t)UINT32_MAX + 1), UINT32_MAX);
        DARK_TEST_EQ_U(dark_sat_ucast_u64(10), 10);

        dark_sat_ucast_u8(122);
        dark_sat_ucast_u16(122);
        dark_sat_ucast_u32(122);
        dark_sat_ucast_u64(122);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_ucast_i8/_i16/_i32/_i64")
    {
        DARK_TEST_EQ_U(dark_sat_ucast_i8(UINT8_MAX), INT8_MAX);
        DARK_TEST_EQ_U(dark_sat_ucast_i16(UINT16_MAX), INT16_MAX);
        DARK_TEST_EQ_U(dark_sat_ucast_i32(UINT32_MAX), INT32_MAX);
        DARK_TEST_EQ_U(dark_sat_ucast_i64(UINT64_MAX), INT64_MAX);

        dark_sat_ucast_i8(122);
        dark_sat_ucast_i16(122);
        dark_sat_ucast_i32(122);
        dark_sat_ucast_i64(122);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_icast_u8/_u16/_u32/_u64")
    {
        DARK_TEST_EQ_U(dark_sat_icast_u8(256), UINT8_MAX);
        DARK_TEST_EQ_U(dark_sat_icast_u16(-1), 0);
        DARK_TEST_EQ_U(dark_sat_icast_u32(-22323), 0);
        DARK_TEST_EQ_U(dark_sat_icast_u64(111), 111);

        dark_ucast_u8(122);
        dark_ucast_u16(122);
        dark_ucast_u32(122);
        dark_ucast_u64(122);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("sat_icast_i8/_i16/_i32/_i64")
    {
        DARK_TEST_EQ_U(dark_sat_icast_i8(-2000), INT8_MIN);
        DARK_TEST_EQ_U(dark_sat_icast_i16(INT64_MAX), INT16_MAX);
        DARK_TEST_EQ_U(dark_sat_icast_i32(INT64_MAX), INT32_MAX);
        DARK_TEST_EQ_U(dark_sat_icast_i64(124), 124);

        dark_icast_i8(-122);
        dark_icast_i16(-122);
        dark_icast_i32(-122);
        dark_icast_i64(-122);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

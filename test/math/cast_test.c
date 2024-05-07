#include <dark/darkstar.h>

int main()
{
    //----------TEST----------
    DARK_TEST("ucast_u8/_u16/_u32/_u64")
    {
        dark_ucast_u8(122);
        dark_ucast_u16(122);
        dark_ucast_u32(122);
        dark_ucast_u64(122);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("ucast_u8/_u16/_u32/_u64")
    {
        dark_ucast_i8(122);
        dark_ucast_i16(122);
        dark_ucast_i32(122);
        dark_ucast_i64(122);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("ucast_u8/_u16/_u32/_u64")
    {
        dark_ucast_u8(122);
        dark_ucast_u16(122);
        dark_ucast_u32(122);
        dark_ucast_u64(122);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("ucast_u8/_u16/_u32/_u64")
    {
        dark_icast_i8(-122);
        dark_icast_i16(-122);
        dark_icast_i32(-122);
        dark_icast_i64(-122);
    }
    //--------------------------

    dark_test_end();

    return DARK_EXIT_SUCCESS;
}

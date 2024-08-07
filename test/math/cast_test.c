#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("ucast_u8/_u16/_u32/_u64/_zu")
    {
        dark_ucast_u8(122);
        dark_ucast_u16(122);
        dark_ucast_u32(122);
        dark_ucast_u64(122);
        dark_ucast_zu(122);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("ucast_i8/_i16/_i32/_i64/_imax")
    {
        dark_ucast_i8(122);
        dark_ucast_i16(122);
        dark_ucast_i32(122);
        dark_ucast_i64(122);
        dark_ucast_imax(122);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("icast_u8/_u16/_u32/_u64/_zu")
    {
        dark_icast_u8(122);
        dark_icast_u16(122);
        dark_icast_u32(122);
        dark_icast_u64(122);
        dark_icast_zu(122);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("icast_i8/_i16/_i32/_i64")
    {
        dark_icast_i8(-122);
        dark_icast_i16(-122);
        dark_icast_i32(-122);
        dark_icast_i64(-122);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}

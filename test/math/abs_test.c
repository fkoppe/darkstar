#include <dark/darkstar.h>

int main()
{
    //----------TEST----------
    DARK_TEST("abs")
    {
        DARK_TEST_EQ_U((uint8_t)-(INT8_MIN+1)+1, dark_abs_i8(INT8_MIN));
        DARK_TEST_EQ_U((uint16_t)-(INT16_MIN+1)+1, dark_abs_i16(INT16_MIN));
        DARK_TEST_EQ_U((uint32_t)-(INT32_MIN+1)+1, dark_abs_i32(INT32_MIN));
        DARK_TEST_EQ_U((uint64_t)-(INT64_MIN+1)+1, dark_abs_i64(INT64_MIN));
        DARK_TEST_EQ_U((uintmax_t)-(INTMAX_MIN+1)+1, dark_abs_imax(INTMAX_MIN));
    }
    //--------------------------

    dark_test_end();

    return DARK_EXIT_SUCCESS;
}

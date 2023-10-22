#include <dark/darkstar.h>

int main()
{
    DARK_TEST_UINT(dark_abs_int8(INT8_MIN) == (uint8_t)-(INT8_MIN+1)+1, dark_abs_int8(INT8_MIN));
    DARK_TEST_UINT(dark_abs_int16(INT16_MIN) == (uint16_t)-(INT16_MIN+1)+1, dark_abs_int16(INT16_MIN));
    DARK_TEST_UINT(dark_abs_int32(INT32_MIN) == (uint32_t)-(INT32_MIN+1)+1, dark_abs_int32(INT32_MIN));
    DARK_TEST_UINT(dark_abs_int64(INT64_MIN) == (uint64_t)-(INT64_MIN+1)+1, dark_abs_int64(INT64_MIN));

    return EXIT_SUCCESS;
}

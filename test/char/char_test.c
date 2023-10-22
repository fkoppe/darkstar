#include <dark/darkstar.h>

int main()
{
    //cstring_test
    DARK_TEST_UINT(dark_cstring_lenght("abcdefghijklmnopqrstuvwxyz") == 26, dark_cstring_lenght("abcdefghijklmnopqrstuvwxyz"));
    DARK_TEST_UINT(dark_cstring_lenght("") == 0, dark_cstring_lenght(""));

    //digit_test
    DARK_TEST_UINT(dark_digit_uint_get(4711, 0) == 1, dark_digit_uint_get(4711, 0));
    DARK_TEST_UINT(dark_digit_uint_get(4711, 1) == 1, dark_digit_uint_get(4711, 1));
    DARK_TEST_UINT(dark_digit_uint_get(4711, 2) == 7, dark_digit_uint_get(4711, 2));
    DARK_TEST_UINT(dark_digit_uint_get(4711, 3) == 4, dark_digit_uint_get(4711, 3));

    DARK_TEST_UINT(dark_digit_int_get(-42, 0) == 2, dark_digit_int_get(-42, 0));
    DARK_TEST_UINT(dark_digit_int_get(-42, 1) == 4, dark_digit_int_get(-42, 1));

    DARK_TEST_UINT(dark_digit_to_char(0) == '0', dark_digit_to_char(0));

    DARK_TEST_UINT(dark_digit_count_uint64(12345) == 5, dark_digit_count_uint64(12345));
    DARK_TEST_UINT(dark_digit_count_uint64(0) == 1, dark_digit_count_uint64(0));

    DARK_TEST_UINT(dark_digit_count_int64(-1) == 1, dark_digit_count_int64(-1));
    DARK_TEST_UINT(dark_digit_count_int64(INT32_MAX) <= DARK_DIGIT_COUNT_INT32_MAX, dark_digit_count_int64(INT32_MAX));

    size_t count = dark_digit_count_uint64(95);
    char buffer[] = "0123456789";

    DARK_TEST_UINT(dark_cstring_lenght(buffer) == DARK_DIGIT_COUNT_INT32_MAX, dark_cstring_lenght(buffer));

    dark_digit_int_to_char_arr(-95, count, buffer);
    DARK_TEST_UINT(dark_cstring_lenght(buffer) == DARK_DIGIT_COUNT_INT32_MAX, dark_cstring_lenght(buffer));

    dark_digit_int_to_char_arr_terminated(-95, count, buffer);
    DARK_TEST_UINT(dark_cstring_lenght(buffer) == 2, dark_cstring_lenght(buffer));

    return EXIT_SUCCESS;
}

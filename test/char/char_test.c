#include <dark/darkstar.h>

int main()
{
    //cstring_test
    DARK_ASSERT(dark_cstring_lenght("abcdefghijklmnopqrstuvwxyz") == 26, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_cstring_lenght("") == 0, DARK_ERROR_UNKNOWN);

    //digit_test
    DARK_ASSERT(dark_digit_get(4711, 1) == 1, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_digit_get(4711, 2) == 1, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_digit_get(4711, 3) == 7, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_digit_get(4711, 4) == 4, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_digit_get(-42, 1) == 2, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_digit_get(-42, 2) == 4, DARK_ERROR_UNKNOWN);

    DARK_ASSERT(dark_digit_to_char(0) == '0', DARK_ERROR_UNKNOWN);

    DARK_ASSERT(dark_digit_count_int32(12345) == 5, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_digit_count_int32(0) == 1, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_digit_count_int32(-1) == 1, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_digit_count_int32(INT32_MAX) <= DARK_DIGIT_COUNT_INT32_MAX, DARK_ERROR_UNKNOWN);

    size_t count = dark_digit_count_int32(95);
    char buffer[DARK_DIGIT_COUNT_INT32_MAX+1] = {'1'};
    buffer[DARK_DIGIT_COUNT_INT32_MAX] = '\n';

    dark_digit_int32_to_char_arr(95, count, buffer);
    DARK_ASSERT(dark_cstring_lenght(buffer) == DARK_DIGIT_COUNT_INT32_MAX, DARK_ERROR_UNKNOWN);

    dark_digit_int32_to_char_arr_terminated(95, count, buffer);
    DARK_ASSERT(dark_cstring_lenght(buffer) == 2, DARK_ERROR_UNKNOWN);

    return EXIT_SUCCESS;
}

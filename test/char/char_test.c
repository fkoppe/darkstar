#include <dark/darkstar.h>

int main()
{
    //cstring_test
    DARK_TEST_EQ_U(26, dark_cstring_lenght("abcdefghijklmnopqrstuvwxyz"));
    DARK_TEST_EQ_U(0, dark_cstring_lenght(""));

    //digit_test
    DARK_TEST_EQ_U(1, dark_digit_get_u(4711, 0));
    DARK_TEST_EQ_U(1, dark_digit_get_u(4711, 1));
    DARK_TEST_EQ_U(7, dark_digit_get_u(4711, 2));
    DARK_TEST_EQ_U(4, dark_digit_get_u(4711, 3));

    DARK_TEST_EQ_U(2, dark_digit_get_i(-42, 0));
    DARK_TEST_EQ_U(4, dark_digit_get_i(-42, 1));

    DARK_TEST_EQ_U('0', dark_digit_to_char(0));

    DARK_TEST_EQ_U(5, dark_digit_count_u64(12345));
    DARK_TEST_EQ_U(1, dark_digit_count_u64(0));

    DARK_TEST_EQ_U(1, dark_digit_count_i64(-1));
    DARK_TEST_LE_U(dark_digit_count_i64(INT32_MAX), DARK_DIGIT_COUNT_MAX_I32);

    size_t count = dark_digit_count_u64(95);
    char buffer[] = "0123456789";

    DARK_TEST_EQ_U(DARK_DIGIT_COUNT_MAX_I32, dark_cstring_lenght(buffer));

    dark_digit_to_char_arr_i(-95, count, buffer);
    DARK_TEST_EQ_U(DARK_DIGIT_COUNT_MAX_I32, dark_cstring_lenght(buffer));

    dark_digit_to_char_arr_i_terminated(-95, count, buffer);
    DARK_TEST_EQ_U(2, dark_cstring_lenght(buffer));

    return EXIT_SUCCESS;
}

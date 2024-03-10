#include <dark/darkstar.h>

int main()
{
    int32_t arr_1[] = {2, 1, 3, 4, 2};
    int32_t arr_2[] = {1, 2, 3};
    int32_t arr_3[] = {1, 1, 3, 4, 2};
    int32_t arr_4[] = {2, 3, 4, 5, 6};

    size_t index = 0;
    const int32_t element = 2;

    //linear
    DARK_TEST(dark_find_linear_index(&element, sizeof(int32_t), 5, arr_1, (Dark_Compare)dark_compare_i32, &index));
    DARK_TEST_EQ_U(0, index);

    DARK_TEST(dark_find_linear_index(&element, sizeof(int32_t), 3, arr_2, (Dark_Compare)dark_compare_i32, &index));
    DARK_TEST_EQ_U(1, index);

    DARK_TEST(dark_find_linear_index(&element, sizeof(int32_t), 5, arr_3, (Dark_Compare)dark_compare_i32, &index));
    DARK_TEST_EQ_U(4, index);

    //linear_reverse
    DARK_TEST(dark_find_linear_reverse_index(&element, sizeof(int32_t), 5, arr_1, (Dark_Compare)dark_compare_i32, &index));
    DARK_TEST_EQ_U(4, index);

    DARK_TEST(dark_find_linear_reverse_index(&element, sizeof(int32_t), 3, arr_2, (Dark_Compare)dark_compare_i32, &index));
    DARK_TEST_EQ_U(1, index);

    DARK_TEST(dark_find_linear_reverse_index(&element, sizeof(int32_t), 5, arr_4, (Dark_Compare)dark_compare_i32, &index));
    DARK_TEST_EQ_U(0, index);

    //binary
    DARK_TEST(dark_find_binary_index(&element, sizeof(int32_t), 3, arr_2, (Dark_Compare)dark_compare_i32, &index));
    DARK_TEST_EQ_U(1, index);

    DARK_TEST(dark_find_binary_index(&element, sizeof(int32_t), 5, arr_4, (Dark_Compare)dark_compare_i32, &index));
    DARK_TEST_EQ_U(0, index);

    return EXIT_SUCCESS;
}
